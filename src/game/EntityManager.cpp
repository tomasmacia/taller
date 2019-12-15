
#include "EntityManager.h"

#include "../entities/components/InputPoller.h"
#include "../entities/components/IA.h"
#include "../entities/components/NullWill.h"

#include "../entities/components/appearances/CharacterAppearance.h"
#include "../entities/components/appearances/EnemyAppearance.h"
#include "../entities/components/SoundHierarchy/CharacterSound.h"
#include "../entities/components/SoundHierarchy/EnemySound.h"
#include "../entities/components/SoundHierarchy/NullSound.h"
#include "../entities/components/SoundHierarchy/BoxSound.h"
#include "../entities/components/SoundHierarchy/BarrelSound.h"

//CONSTRUCTOR
//=========================================================================================
EntityManager::EntityManager(Controller* controller, Config* config){
    packagesToClients = new list<Sendable*>();
    initializeCollitionManager();

    this->controller = controller;
    this->config = config;
}

void EntityManager::initializeCollitionManager(){
    LogManager::logDebug("[LEVEL]: Inicializando Collition EntityManager");
    collitionManager = new CollitionManager();
}

//API
//=========================================================================================
void EntityManager::update() {//se updatean todas seguro porque updateo las listas que formaban una particion de las entities

    for(auto* e : backLayerBackgrounds) e->update();
    for(auto* e : physicalEntities) e->update();
    for(auto* e : frontLayerBackgrounds) e->update();
    for(auto* e : specialEntities) e->update();

    eraseDeadEntities();
}

std::list<Sendable*>* EntityManager::generateSendables() {

    //clear previous outdated packages
    for (auto package: *packagesToClients){
        delete package;
        package = nullptr;
    }
    packagesToClients->clear();

    sortEntitiesByZ();

    for(auto* e : backLayerBackgrounds){
        packagesToClients->splice(packagesToClients->end(),e->generateSendable());
    }

    for(auto* e : physicalEntities){
        packagesToClients->splice(packagesToClients->end(),e->generateSendable());
    }

    for(auto* e : frontLayerBackgrounds){
        packagesToClients->splice(packagesToClients->end(),e->generateSendable());
    }

    return packagesToClients;
}

void EntityManager::prepareForNextLevel(){

    collitionManager->prepareForNextLevel();
    physicalEntities.clear();
    destroyNonLevelPersistentEntities();
    enemies.clear();
    unanimatedEntities.clear();
    backLayerBackgrounds.clear();
    frontLayerBackgrounds.clear();

    for (Character* e : players){
        physicalEntities.push_back(e);
    }
}

void EntityManager::reconectPlayerByID(int id, int newID) {
    for (auto player : players){
        if (player->getID() == id){
            player->setConnected(newID);
        }
    }
}

void EntityManager::disconectPlayerByID(int id){
    for (auto player : players){
        if (player->getID() == id){
            player->setDisconnected();
        }
    }
}

void EntityManager::setLevelParameters(int levelWidth, int levelHeight, int levelDepth) {

    validPositionGenerator.set(levelWidth,levelHeight,levelDepth);
}

//ADDING NEW ENTITIES
//=========================================================================================
Character* EntityManager::addPlayer(int x, int y, int z, int id) {
    Character* character = createCharacter(x,y,z,id);
    players.push_back(character);
    physicalEntities.push_back(character);
    return character;
}

void EntityManager::addEnemy() {
    Enemy* enemy = createEnemy();
    nonLevelPersistentEntities.push_back((Entity*) enemy);
    enemies.push_back(enemy);
    physicalEntities.push_back(enemy);
}

void EntityManager::addKnife() {
    auto* knife = createKnife();
    nonLevelPersistentEntities.push_back((Entity*) knife);
    unanimatedEntities.push_back(knife);
    physicalEntities.push_back(knife);
}

void EntityManager::addTube() {
    auto* tube = createTube();
    nonLevelPersistentEntities.push_back((Entity*) tube);
    unanimatedEntities.push_back(tube);
    physicalEntities.push_back(tube);
}

void EntityManager::addBox() {
    auto* box = createBox();
    nonLevelPersistentEntities.push_back((Entity*) box);
    unanimatedEntities.push_back(box);
    physicalEntities.push_back(box);
}

void EntityManager::addBarrel() {
    auto* barrel = createBarrel();
    nonLevelPersistentEntities.push_back((Entity*) barrel);
    unanimatedEntities.push_back(barrel);
    physicalEntities.push_back(barrel);
}

void EntityManager::addFar(const string &spritePath, float parallaxSpeed) {
    auto* background = createFar(spritePath,parallaxSpeed);
    nonLevelPersistentEntities.push_back(background);
    backLayerBackgrounds.push_back(background);
}

void EntityManager::addMiddle(const string &spritePath, float parallaxSpeed) {
    auto* background = createMiddle(spritePath,parallaxSpeed);
    nonLevelPersistentEntities.push_back(background);
    backLayerBackgrounds.push_back(background);
}

void EntityManager::addFloor(const string &spritePath, float parallaxSpeed) {
    auto* background = createFloor(spritePath,parallaxSpeed);
    nonLevelPersistentEntities.push_back(background);
    backLayerBackgrounds.push_back(background);
}

void EntityManager::addOverlay(const string &spritePath, float parallaxSpeed) {
    auto* background = createOverlay(spritePath,parallaxSpeed);
    nonLevelPersistentEntities.push_back(background);
    frontLayerBackgrounds.push_back(background);
}

Screen* EntityManager::addScreen(int screenWidth, int screenHeight, int levelWidth, int levelDepth) {
    screen = new Screen(screenWidth, screenHeight, levelWidth, levelDepth, collitionManager);
    specialEntities.push_back((Entity*) screen);
    return screen;
}

//ADDING NEW ENTITIESl
//=========================================================================================
Character *EntityManager::createCharacter(int x, int y, int z, int id) {

    int w = (int)(((float)config->screenResolution.width)*CHARACTER_WIDTH_SCALE);
    int h = (int)((float)config->screenResolution.height*CHARACTER_HEIGHT_SCALE);
    int walkingSpeed = ((float)config->screenResolution.width) * WAKING_SPEED_FACTOR;
    int jumpingSpeed = ((float)config->screenResolution.height) * JUMPING_SPEED_FACTOR;

    int centerX = x + w/2;
    int centerY = y + h/2;
    int centerZ = z + DEFAULT_COLLITION_BOX_DEPTH/2;

    auto* idComponent = new ID(id);
    auto* will = new InputPoller(controller, idComponent);
    auto* state = new State(will);

    auto* collitionBox = collitionManager->createCharacterBlockingCollitionBox(centerX, centerY, centerZ, w * NORMAL_COLLITON_BOX_SCALE_FACTOR_WIDTH, h * NORMAL_COLLITON_BOX_SCALE_FACTOR_HEIGHT, DEFAULT_COLLITION_BOX_DEPTH,VISUAL_COLLITION_BOX);
    auto* pickBox = new CollitionBox(centerX, centerY, centerZ, w, h, DEFAULT_COLLITION_BOX_DEPTH * PICK_COLLITON_BOX_SCALE_FACTOR, collitionBox->getID(),false);
    auto* punchBox = new CollitionBox(centerX, centerY, centerZ, w * ATTACK_COLLITON_BOX_SCALE_FACTOR, h, DEFAULT_COLLITION_BOX_DEPTH * ATTACK_COLLITON_BOX_SCALE_FACTOR,collitionBox->getID(),false);
    auto* kickBox = new CollitionBox(centerX, centerY, centerZ, w * ATTACK_COLLITON_BOX_SCALE_FACTOR, h, DEFAULT_COLLITION_BOX_DEPTH * ATTACK_COLLITON_BOX_SCALE_FACTOR,collitionBox->getID(),false);
    auto* collitionHandler = new AnimatedEntityCollitionHandler(collitionManager, punchBox, kickBox, collitionBox, pickBox);

    auto* position = new Position(centerX, centerY, centerZ, collitionHandler);
    auto* physics = new Physics(state,position,walkingSpeed,jumpingSpeed);
    auto* screenPosition = new ScreenPosition(w,h,DEFAULT_COLLITION_BOX_DEPTH,position,screen);

    if (VISUAL_COLLITION_BOX){
        collitionHandler->setToAllCollitionBoxScreenPosition(screenPosition);
    }

    auto characterConfig = config->gameplay.characters.at(players.size());
    auto* appearance = new CharacterAppearance(w, h,position, screenPosition, state, characterConfig);
    auto* sound = new CharacterSound(state,config->sounds);
    auto* damage = new Damage();
    auto* life = new Life(state);
    auto* score = new Score();
    auto* scoreAppearance = new ScoreAppearance(screenPosition, score);
    auto* attack = new Attack(state, collitionHandler);

    return new Character(collitionHandler, life, damage, score, position,
                          state, screenPosition, appearance, sound,
                          will, physics, attack, idComponent, scoreAppearance,w,h,DEFAULT_COLLITION_BOX_DEPTH);
}


Enemy *EntityManager::createEnemy() {

    int w = (int)((float)config->screenResolution.width*ENEMY_WIDTH_SCALE);
    int h = (int)((float)config->screenResolution.height*ENEMY_HEIGHT_SCALE);
    int walkingSpeed = config->screenResolution.width * WAKING_SPEED_FACTOR;
    int jumpingSpeed = config->screenResolution.height * JUMPING_SPEED_FACTOR;

    int x = validPositionGenerator.x();
    int y = validPositionGenerator.y();
    int z = validPositionGenerator.z();

    int centerX = x + w/2;
    int centerY = y + h/2;
    int centerZ = z + DEFAULT_COLLITION_BOX_DEPTH/2;


    auto* collitionBox = collitionManager->createEnemyBlockingCollitionBox(centerX, centerY, centerZ, w * NORMAL_COLLITON_BOX_SCALE_FACTOR_WIDTH, h * NORMAL_COLLITON_BOX_SCALE_FACTOR_HEIGHT, DEFAULT_COLLITION_BOX_DEPTH,VISUAL_COLLITION_BOX);
    auto* pickBox = new CollitionBox(centerX, centerY, centerZ, w, h, DEFAULT_COLLITION_BOX_DEPTH * PICK_COLLITON_BOX_SCALE_FACTOR, collitionBox->getID(),false);
    auto* punchBox = new CollitionBox(centerX, centerY, centerZ, w * ATTACK_COLLITON_BOX_SCALE_FACTOR, h, DEFAULT_COLLITION_BOX_DEPTH * ATTACK_COLLITON_BOX_SCALE_FACTOR,collitionBox->getID(),false);
    auto* kickBox = new CollitionBox(centerX, centerY, centerZ, w * ATTACK_COLLITON_BOX_SCALE_FACTOR, h, DEFAULT_COLLITION_BOX_DEPTH * ATTACK_COLLITON_BOX_SCALE_FACTOR,collitionBox->getID(),false);
    auto* collitionHandler = new AnimatedEntityCollitionHandler(collitionManager, punchBox, kickBox, collitionBox, pickBox);


    auto* position = new Position(centerX, centerY, centerZ, collitionHandler);
    auto* screenPosition = new ScreenPosition(w,h,DEFAULT_COLLITION_BOX_DEPTH,position,screen);

    auto* will = new IA(this, position);
    // auto* will = new NullWill();
    auto* state = new State(will);
    auto* physics = new Physics(state,position,walkingSpeed,jumpingSpeed);

    if (VISUAL_COLLITION_BOX){
        collitionHandler->setToAllCollitionBoxScreenPosition(screenPosition);
    }

    auto* appearance = new EnemyAppearance(w, h, screenPosition, state, config->gameplay.npcs.front());
    auto* sound = new EnemySound(state,config->sounds);
    auto* damage = new Damage();
    auto* life = new Life(state);
    auto* score = new Score();
    auto* attack = new Attack(state, collitionHandler);

    return new Enemy(collitionHandler, life, damage, score, position,
                     state, screenPosition, appearance, sound,
                     will, physics, attack,w,h,DEFAULT_COLLITION_BOX_DEPTH);
}

Knife* EntityManager::createKnife() {

    int w = (int)((float)config->screenResolution.width*WEAPON_WIDTH_SCALE);
    int h = (int)((float)config->screenResolution.height*WEAPON_HEIGHT_SCALE);

    int x = validPositionGenerator.x();
    int y = validPositionGenerator.y();
    int z = validPositionGenerator.z();

    int centerX = x + w/2;
    int centerY = y + h/2;
    int centerZ = z + DEFAULT_COLLITION_BOX_DEPTH/2;

    auto* collitionBox = collitionManager->createKnifeBlockingCollitionBox(centerX, centerY, centerZ, w * NORMAL_COLLITON_BOX_SCALE_FACTOR_WIDTH, h * NORMAL_COLLITON_BOX_SCALE_FACTOR_HEIGHT, DEFAULT_COLLITION_BOX_DEPTH,VISUAL_COLLITION_BOX);
    auto* collitionHandler = new CollitionHandler(collitionManager);
    collitionHandler->addCollitionBox(collitionBox);

    auto* damage = new Damage();
    auto* score = new Score();
    auto* position = new Position(centerX, centerY, centerZ, collitionHandler);
    auto* will = new NullWill();
    auto* state = new State(will);
    auto* life = new Life(state);
    auto* screenPosition = new ScreenPosition(w,h,DEFAULT_COLLITION_BOX_DEPTH,position,screen);

    if (VISUAL_COLLITION_BOX){
        collitionHandler->setToAllCollitionBoxScreenPosition(screenPosition);
    }

    auto* appearance = new KnifeAppearance(w, h, screenPosition, state, config->gameplay.weapons.knife);
    auto* sound = new NullSound(state,config->sounds);

    return new Knife(collitionHandler,
                     life, damage, score, position,
                     state, screenPosition, appearance, sound,w,h,DEFAULT_COLLITION_BOX_DEPTH);
}

Tube* EntityManager::createTube() {

    int w = (int)((float)config->screenResolution.width*WEAPON_WIDTH_SCALE);
    int h = (int)((float)config->screenResolution.height*WEAPON_HEIGHT_SCALE);

    int x = validPositionGenerator.x();
    int y = validPositionGenerator.y();
    int z = validPositionGenerator.z();

    int centerX = x + w/2;
    int centerY = y + h/2;
    int centerZ = z + DEFAULT_COLLITION_BOX_DEPTH/2;

    auto* collitionBox = collitionManager->createTubeBlockingCollitionBox(centerX, centerY, centerZ, w * NORMAL_COLLITON_BOX_SCALE_FACTOR_WIDTH, h * NORMAL_COLLITON_BOX_SCALE_FACTOR_HEIGHT, DEFAULT_COLLITION_BOX_DEPTH,VISUAL_COLLITION_BOX);
    auto* collitionHandler = new CollitionHandler(collitionManager);
    collitionHandler->addCollitionBox(collitionBox);

    auto* damage = new Damage();
    auto* score = new Score();
    auto* position = new Position(centerX, centerY, centerZ, collitionHandler);
    auto* will = new NullWill();
    auto* state = new State(will);
    auto* life = new Life(state);
    auto* screenPosition = new ScreenPosition(w,h,DEFAULT_COLLITION_BOX_DEPTH,position,screen);

    if (VISUAL_COLLITION_BOX){
        collitionHandler->setToAllCollitionBoxScreenPosition(screenPosition);
    }

    auto* appearance = new TubeAppearance(w, h, screenPosition, state, config->gameplay.weapons.tube);
    auto* sound = new NullSound(state,config->sounds);

    return new Tube(collitionHandler,
                    life, damage, score, position,
                    state, screenPosition, appearance, sound,w,h,DEFAULT_COLLITION_BOX_DEPTH);
}

Box* EntityManager::createBox() {

    int w = (int)((float)config->screenResolution.width*UTILITY_WIDTH_SCALE);
    int h = (int)((float)config->screenResolution.height*UTILITY_HEIGHT_SCALE);

    int x = validPositionGenerator.x();
    int y = validPositionGenerator.y();
    int z = validPositionGenerator.z();

    int centerX = x + w/2;
    int centerY = y + h/2;
    int centerZ = z + DEFAULT_COLLITION_BOX_DEPTH/2;

    auto* collitionBox = collitionManager->createBoxBlockingCollitionBox(centerX, centerY, centerZ,w * NORMAL_COLLITON_BOX_SCALE_FACTOR_WIDTH, h * NORMAL_COLLITON_BOX_SCALE_FACTOR_HEIGHT, DEFAULT_COLLITION_BOX_DEPTH,VISUAL_COLLITION_BOX);
    auto* collitionHandler = new CollitionHandler(collitionManager);
    collitionHandler->addCollitionBox(collitionBox);

    auto* damage = new Damage();
    auto* score = new Score();
    auto* position = new Position(centerX, centerY, centerZ, collitionHandler);
    auto* will = new NullWill();
    auto* state = new State(will);
    auto* life = new Life(state);
    auto* screenPosition = new ScreenPosition(w,h,DEFAULT_COLLITION_BOX_DEPTH,position,screen);

    if (VISUAL_COLLITION_BOX){
        collitionHandler->setToAllCollitionBoxScreenPosition(screenPosition);
    }

    auto* appearance = new BoxAppearance(w, h, screenPosition, state, config->gameplay.utilities.box);
    auto* sound = new BoxSound(state,config->sounds);

    return new Box(collitionHandler,
                   life, damage, score, position,
                   state, screenPosition, appearance, sound,w,h,DEFAULT_COLLITION_BOX_DEPTH);
}

Barrel* EntityManager::createBarrel() {

    int w = (int)((float)config->screenResolution.width*UTILITY_WIDTH_SCALE);
    int h = (int)((float)config->screenResolution.height*UTILITY_HEIGHT_SCALE);

    int x = validPositionGenerator.x();
    int y = validPositionGenerator.y();
    int z = validPositionGenerator.z();

    int centerX = x + w/2;
    int centerY = y + h/2;
    int centerZ = z + DEFAULT_COLLITION_BOX_DEPTH/2;

    auto* collitionBox = collitionManager->createBarrelBlockingCollitionBox(centerX, centerY, centerZ,w * NORMAL_COLLITON_BOX_SCALE_FACTOR_WIDTH, h * NORMAL_COLLITON_BOX_SCALE_FACTOR_HEIGHT, DEFAULT_COLLITION_BOX_DEPTH,VISUAL_COLLITION_BOX);
    auto* collitionHandler = new CollitionHandler(collitionManager);
    collitionHandler->addCollitionBox(collitionBox);

    auto* damage = new Damage();
    auto* score = new Score();
    auto* position = new Position(centerX, centerY, centerZ, collitionHandler);
    auto* will = new NullWill();
    auto* state = new State(will);
    auto* life = new Life(state);
    auto* screenPosition = new ScreenPosition(w,h,DEFAULT_COLLITION_BOX_DEPTH,position,screen);

    if (VISUAL_COLLITION_BOX){
        collitionHandler->setToAllCollitionBoxScreenPosition(screenPosition);
    }

    auto* appearance = new BarrelAppearance(w, h, screenPosition, state, config->gameplay.utilities.barrel);
    auto* sound = new BarrelSound(state,config->sounds);

    return new Barrel(collitionHandler,
                      life, damage, score, position,
                      state, screenPosition, appearance, sound,w,h,DEFAULT_COLLITION_BOX_DEPTH);
}

Background* EntityManager::createFar(const string& spritePath, float parallaxSpeed) {

    auto* appearance = new BackgroundAppearance(nullptr, screen, spritePath, parallaxSpeed);
    return new Background(appearance);
}

Background* EntityManager::createMiddle(const string& spritePath, float parallaxSpeed) {

    auto* appearance = new BackgroundAppearance(nullptr, screen, spritePath, parallaxSpeed);
    return new Background(appearance);
}

Background* EntityManager::createFloor(const string& spritePath, float parallaxSpeed) {

    int w = screen->getLevelWidth();
    int h = config->screenResolution.height;
    int d = screen->getLevelDepth();

    int centerXBack = 0 + w/2;
    int centerYBack = 0 + h/2;
    int centerZBack = d + DEFAULT_COLLITION_BOX_DEPTH/2;

    int centerXFront = 0 + w/2;
    int centerYFront = 0 + h/2;
    int centerZFront = 0 - DEFAULT_COLLITION_BOX_DEPTH/2;

    int centerXFloor = 0 + w/2;
    int centerYFloor = 0 - DEFAULT_COLLITION_BOX_HEIGHT;
    int centerZFloor = 0 + d/2 ;

    auto* collitionBoxes = new list<CollitionBox *>();
    auto* back = collitionManager->createBackgroundBlockingCollitionBox(centerXBack, centerYBack, centerZBack, w, h, DEFAULT_COLLITION_BOX_DEPTH,VISUAL_COLLITION_BOX);
    auto* front = collitionManager->createBackgroundBlockingCollitionBox(centerXFront, centerYFront, centerZFront, w, h, DEFAULT_COLLITION_BOX_DEPTH,VISUAL_COLLITION_BOX);
    auto* floor = collitionManager->createBackgroundBlockingCollitionBox(centerXFloor,centerYFloor,centerZFloor, w, DEFAULT_COLLITION_BOX_HEIGHT, screen->getLevelDepth(),VISUAL_COLLITION_BOX);
    collitionBoxes->push_back(back);
    collitionBoxes->push_back(front);
    collitionBoxes->push_back(floor);

    auto* appearance = new BackgroundAppearance(nullptr, screen, spritePath, parallaxSpeed);

    auto* collitionHandler = new BackgroundCollitionHandler(collitionManager, collitionBoxes);


    return new Background(collitionHandler,appearance);
}

Background* EntityManager::createOverlay(const string& spritePath, float parallaxSpeed) {

    auto* appearance = new BackgroundAppearance(nullptr, screen, spritePath, parallaxSpeed);
    return new Background(appearance);
}

//DESTROY
//=========================================================================================
void EntityManager::destroyAllEntities() { //se destruyen todas seguro porque borro las listas que formaban una particion de las entities
    for(auto* e : physicalEntities) {
        delete e;
        e = nullptr;
    }
    for(auto* e : specialEntities){
        delete e;
        e = nullptr;
    }
    for(auto* e : backLayerBackgrounds) {
        delete e;
        e = nullptr;
    }
    for(auto* e : frontLayerBackgrounds) {
        delete e;
        e = nullptr;
    }
}

void EntityManager::eraseDeadEntities() {

    list<PhysicalEntity*> toUntrack;
    for (auto e: physicalEntities){
        if (e->dead()){
            delete(e);
            cout<<"a dead entity has been correctly eliminated from the game"<<endl;
            toUntrack.push_back(e);
        }
    }
    for (auto e: toUntrack){
        untrackDead(e);
    }
}

void EntityManager::untrackDead(PhysicalEntity *entity) {

    nonLevelPersistentEntities.remove((Entity*) entity);
    players.remove((Character*) entity);
    enemies.remove((Enemy*) entity);
    unanimatedEntities.remove((UnanimatedEntity*) entity);
    specialEntities.remove((Entity*) entity);
    physicalEntities.remove(entity);
}

void EntityManager::destroyNonLevelPersistentEntities() {
    for(auto* e : nonLevelPersistentEntities){
        delete e;
        e = nullptr;
    }
    nonLevelPersistentEntities.clear();
}

EntityManager::~EntityManager() {
    destroyAllEntities();
    physicalEntities.clear();
    enemies.clear();
    unanimatedEntities.clear();
    specialEntities.clear();
    nonLevelPersistentEntities.clear();
    players.clear();
    backLayerBackgrounds.clear();
    frontLayerBackgrounds.clear();

    for (auto package: *packagesToClients){
        delete package;
    }
    packagesToClients->clear();
    delete packagesToClients;
    packagesToClients = nullptr;

    delete collitionManager;
    collitionManager = nullptr;
}

//SORTING
//=========================================================================================
struct EntityComparator
{
    bool operator ()(PhysicalEntity* entity1, PhysicalEntity* entity2)
    {
        int entity1Z = entity1->getZ();
        int entity2Z = entity2->getZ();

        if(entity1Z == entity2Z)
            return true;
        return entity1Z > entity2Z;
    }
};

void EntityManager::sortEntitiesByZ() {
    physicalEntities.sort(EntityComparator());
}

Box* EntityManager::createBox(int x, int y, int z) {

    int w = (int)((float)config->screenResolution.width*UTILITY_WIDTH_SCALE);
    int h = (int)((float)config->screenResolution.height*UTILITY_HEIGHT_SCALE);

    int centerX = x + w/2;
    int centerY = y + h/2;
    int centerZ = z + DEFAULT_COLLITION_BOX_DEPTH/2;

    auto* collitionBox = collitionManager->createBoxBlockingCollitionBox(centerX, centerY, centerZ,w * NORMAL_COLLITON_BOX_SCALE_FACTOR_WIDTH, h * NORMAL_COLLITON_BOX_SCALE_FACTOR_HEIGHT, DEFAULT_COLLITION_BOX_DEPTH,VISUAL_COLLITION_BOX);
    auto* collitionHandler = new CollitionHandler(collitionManager);
    collitionHandler->addCollitionBox(collitionBox);

    auto* damage = new Damage();
    auto* score = new Score();
    auto* position = new Position(centerX, centerY, centerZ, collitionHandler);
    auto* will = new NullWill();
    auto* state = new State(will);
    auto* life = new Life(state);
    auto* screenPosition = new ScreenPosition(w,h,DEFAULT_COLLITION_BOX_DEPTH,position,screen);

    if (VISUAL_COLLITION_BOX){
        collitionHandler->setToAllCollitionBoxScreenPosition(screenPosition);
    }

    auto* appearance = new BoxAppearance(w, h, screenPosition, state, config->gameplay.utilities.box);
    auto* sound = new BoxSound(state,config->sounds);

    return new Box(collitionHandler,
                   life, damage, score, position,
                   state, screenPosition, appearance, sound,w,h,DEFAULT_COLLITION_BOX_DEPTH);
}

void EntityManager::addBox(int x, int y, int z) {
    auto* box = createBox(x,y,z);
    nonLevelPersistentEntities.push_back((Entity*) box);
    unanimatedEntities.push_back(box);
    physicalEntities.push_back(box);
}

void EntityManager::addEnemy(int x, int y, int z) {
    Enemy* enemy = createEnemy(x,y,z);
    nonLevelPersistentEntities.push_back((Entity*) enemy);
    enemies.push_back(enemy);
    physicalEntities.push_back(enemy);
}

Enemy *EntityManager::createEnemy(int x, int y, int z) {
    int w = (int)((float)config->screenResolution.width*ENEMY_WIDTH_SCALE);
    int h = (int)((float)config->screenResolution.height*ENEMY_HEIGHT_SCALE);
    int walkingSpeed = config->screenResolution.width * WAKING_SPEED_FACTOR;
    int jumpingSpeed = config->screenResolution.height * JUMPING_SPEED_FACTOR;

    int centerX = x + w/2;
    int centerY = y + h/2;
    int centerZ = z + DEFAULT_COLLITION_BOX_DEPTH/2;


    auto* collitionBox = collitionManager->createEnemyBlockingCollitionBox(centerX, centerY, centerZ, w * NORMAL_COLLITON_BOX_SCALE_FACTOR_WIDTH, h * NORMAL_COLLITON_BOX_SCALE_FACTOR_HEIGHT, DEFAULT_COLLITION_BOX_DEPTH,VISUAL_COLLITION_BOX);
    auto* pickBox = new CollitionBox(centerX, centerY, centerZ, w, h, DEFAULT_COLLITION_BOX_DEPTH * PICK_COLLITON_BOX_SCALE_FACTOR, collitionBox->getID(),false);
    auto* punchBox = new CollitionBox(centerX, centerY, centerZ, w * ATTACK_COLLITON_BOX_SCALE_FACTOR, h, DEFAULT_COLLITION_BOX_DEPTH * ATTACK_COLLITON_BOX_SCALE_FACTOR,collitionBox->getID(),false);
    auto* kickBox = new CollitionBox(centerX, centerY, centerZ, w * ATTACK_COLLITON_BOX_SCALE_FACTOR, h, DEFAULT_COLLITION_BOX_DEPTH * ATTACK_COLLITON_BOX_SCALE_FACTOR,collitionBox->getID(),false);
    auto* collitionHandler = new AnimatedEntityCollitionHandler(collitionManager, punchBox, kickBox, collitionBox, pickBox);


    auto* position = new Position(centerX, centerY, centerZ, collitionHandler);
    auto* screenPosition = new ScreenPosition(w,h,DEFAULT_COLLITION_BOX_DEPTH,position,screen);

    auto* will = new IA(this, position);
    //auto* will = new NullWill();
    auto* state = new State(will);
    auto* physics = new Physics(state,position,walkingSpeed,jumpingSpeed);

    if (VISUAL_COLLITION_BOX){
        collitionHandler->setToAllCollitionBoxScreenPosition(screenPosition);
    }

    auto* appearance = new EnemyAppearance(w, h, screenPosition, state, config->gameplay.npcs.front());
    auto* sound = new EnemySound(state,config->sounds);
    auto* damage = new Damage();
    auto* life = new Life(state);
    auto* score = new Score();
    auto* attack = new Attack(state, collitionHandler);

    return new Enemy(collitionHandler, life, damage, score, position,
                     state, screenPosition, appearance, sound,
                     will, physics, attack,w,h,DEFAULT_COLLITION_BOX_DEPTH);
}

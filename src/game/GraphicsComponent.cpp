#include "GraphicsComponent.h"
#include "../LogLib/LogManager.h"
#include "Game.h"

GraphicsComponent::GraphicsComponent(int width, int height, PhysicsComponent* physicsComponent){
    //Sets some objects
    _physicsComponent = physicsComponent;
    _renderer = Game::getInstance().renderer;

    //Initializes destination square
    updatePosition();
    _destinationRect.w = width;
    _destinationRect.h = height;
}

GraphicsComponent::~GraphicsComponent(){
    SDL_DestroyTexture(_currentSprite);
}

void GraphicsComponent::update(){

    if (_type == UNDEFINED)
        LogManager::logError("GraphicsComponent: tried to update undefined type");

    updatePosition();
    loadNextImage();
}

void GraphicsComponent::render(){
    SDL_RenderCopy( _renderer, _currentSprite, &_sourceRect, &_destinationRect);
}

void GraphicsComponent::setPosition(int x, int y){
    _destinationRect.x = x;
    _destinationRect.y = y;
}

void GraphicsComponent::setType(GameObjectType gameObjectType){
    //Initializes type of graphic component and sprites                                      
    _type = gameObjectType;
    setSpritesAcordingToType();
    _current_sprites_path = _neutral_sprites_path;
    loadSprite(); // i think in memory
}

void GraphicsComponent::switchAction(Action action){

    if (_action ==  NONE){  //si hay una accion que no es NONE no se cambia
        _action = action;
        switch (action)
        {
        case UP:
            _current_sprites_path = _walk_sprites_path;
            break;
        case DOWN:
            _current_sprites_path = _walk_sprites_path;
            break;
        case LEFT:
            if (notFliped())
                flip();
            _current_sprites_path = _walk_sprites_path;
            break;
        case RIGHT:
            if (notFliped())
                flip();
            _current_sprites_path = _walk_sprites_path;
            break;
        case JUMP:
            _current_sprites_path = _jump_sprites_path;
            break;
        case PUNCH:
            _current_sprites_path = _punch_sprites_path;
            break;
        case KICK:
            _current_sprites_path = _kick_sprites_path;
            break;
        case JUMP_KICK:
            _current_sprites_path = _jump_kick_sprites_path;
            break;
        case CROUCH:
            _current_sprites_path = _crouch_sprites_path;
            break;
    }
    }
}

void GraphicsComponent::setSpritesAcordingToType(){

    switch (_type)
    {
        case CHARACTER:
            setCharacterWalkSprites();
            setCharacterJumpSprites();
            setCharacterPunchSprites();
            setCharacterKickSprites();
            setCharacterJumpKickSprites();
            setCharacterCrouchSprites();
            setCharacterNeutralSprites();
            break;
        /*
        case ENEMY:
            setEnemyWalkSprites();
            //setEnemyJumpSprites();
            //setEnemyPunchSprites();
            //setEnemyKickSprites();
            //setEnemyJumpKickSprites();
            //setEnemyCrouchSprites();
            //setEnemyNeutralSprites();
            break;
        case BARREL:
            setBarrelNeutralSprites();
            break;
        case BOX:
            setBoxNeutralSprites();
            break;
        case TUBE:
            setTubeNeutralSprites();
            break;
        case KNIFE:
            setKnifeNeutralSprites();
            break;
        case BACKGROUND_FLOOR:
            setBackgroundFloorSprites();
            break;
        case BACKGROUND_MIDDLE:
            setBackgroundMiddleSprites();
            break;
        case BACKGROUND_FAR:
            setBackgroundFarSprites();
            break;
        case BACKGROUND_OVERLAY:
            setBackgroundOverlaySprites();
            break;
        */
        case UNDEFINED:
            LogManager::logError("undefined game object type");
            break;
    }
}

bool GraphicsComponent::notFliped(){
    return !_fliped;
}

void GraphicsComponent::flip(){
    _fliped = true;
}

void GraphicsComponent::updatePosition(){
    _destinationRect.x = _physicsComponent->getX();
    _destinationRect.y = _physicsComponent->getY();
}

void GraphicsComponent::loadSprite(){

    SDL_Surface* loadedSurface = IMG_Load( _current_sprites_path.c_str() );
    if( loadedSurface == NULL )
    {
        LogManager::logError("Unable to load image, SDL_image Error:");
    }
    else
    {
        _currentSprite = SDL_CreateTextureFromSurface( _renderer, loadedSurface );
        if( _currentSprite == NULL )
        {
            LogManager::logError( "Unable to create texture from, SDL Error:");
        }
        SDL_FreeSurface( loadedSurface );
    }
}

void GraphicsComponent::loadNextImage(){
    int width, height;
    SDL_QueryTexture(_currentSprite, NULL, NULL, &width, &height);

    _sourceRect.h = height;
    _sourceRect.w = width/_imageAmount;
    _sourceRect.x = ((int)(width/_imageAmount))*_actionCounter;
    _sourceRect.y = height;
}

























//PRIVATE
void GraphicsComponent::setCharacterWalkSprites(){
    _walk_sprites_path = Game::getInstance().getConfig()->gameplay.characters.at(0).walk;  
}

void GraphicsComponent::setCharacterJumpSprites(){
    _walk_sprites_path = Game::getInstance().getConfig()->gameplay.characters.at(0).jump;
}

void GraphicsComponent::setCharacterPunchSprites(){
    _walk_sprites_path = Game::getInstance().getConfig()->gameplay.characters.at(0).punch;
}

void GraphicsComponent::setCharacterKickSprites(){
    _walk_sprites_path = Game::getInstance().getConfig()->gameplay.characters.at(0).kick;
}

void GraphicsComponent::setCharacterJumpKickSprites(){
    _walk_sprites_path = Game::getInstance().getConfig()->gameplay.characters.at(0).jumpkick;
}

void GraphicsComponent::setCharacterCrouchSprites(){
    _walk_sprites_path = Game::getInstance().getConfig()->gameplay.characters.at(0).crouch;
}

void GraphicsComponent::setCharacterNeutralSprites(){
    _neutral_sprites_path = Game::getInstance().getConfig()->gameplay.characters.at(0).stand;
}
/*
void GraphicsComponent::setEnemyWalkSprites(){
    _walk_sprites_path = Game::getInstance().getConfig()->gameplay.npcs.at(0).walk;
}

void GraphicsComponent::setBarrelNeutralSprites(){
    _neutral_sprites_path = Game::getInstance().getConfig()->gameplay.utilities.barrel;
}

void GraphicsComponent::setBoxNeutralSprites(){
    _neutral_sprites_path = Game::getInstance().getConfig()->gameplay.utilities.box;
}

void GraphicsComponent::setTubeNeutralSprites(){
    _neutral_sprites_path = Game::getInstance().getConfig()->gameplay.weapons.tube;
}

void GraphicsComponent::setKnifeNeutralSprites(){
    _neutral_sprites_path = Game::getInstance().getConfig()->gameplay.weapons.knife;
}

void GraphicsComponent::setBackgroundFloorSprites(){
    //IMPLEMENTAR
}

void GraphicsComponent::setBackgroundMiddleSprites(){
    //IMPLEMENTAR
}

void GraphicsComponent::setBackgroundFarSprites(){
    //IMPLEMENTAR
}

void GraphicsComponent::setBackgroundOverlaySprites(){
    //IMPLEMENTAR
}
*/
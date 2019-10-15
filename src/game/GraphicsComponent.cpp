#include "GraphicsComponent.h"
#include "TextureManager.h"
#include "LogManager.h"
#include "game.h"

GraphicsComponent::GraphicsComponent(const char* textureFile){
    _currentSprite = TextureManager::loadTexture(textureFile);
}

GraphicsComponent::~GraphicsComponent(){
    SDL_DestroyTexture(_currentSprite);
}

void GraphicsComponent::update(){

}

void GraphicsComponent::render(){

}

void GraphicsComponent::setPosition(int x, int y){
    _destinationRect.x = x;
    _destinationRect.y = y;
}

void GraphicsComponent::setType(GameObjectType gameObjectType){
    _type = gameObjectType;
    setSpritesAcordingToType();
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








































//PRIVATE
void GraphicsComponent::setCharacterWalkSprites(){
    _walk_sprites_path = Game::->getInstance().getConfig()->gameplay.characters.at(0).walk;  
}

void GraphicsComponent::setCharacterJumpSprites(){
    _walk_sprites_path = Game::->getInstance().getConfig()->gameplay.characters.at(0).jump;
}

void GraphicsComponent::setCharacterPunchSprites(){
    _walk_sprites_path = Game::->getInstance().getConfig()->gameplay.characters.at(0).punch;
}

void GraphicsComponent::setCharacterKickSprites(){
    _walk_sprites_path = Game::->getInstance().getConfig()->gameplay.characters.at(0).kick;
}

void GraphicsComponent::setCharacterJumpKickSprites(){
    _walk_sprites_path = Game::->getInstance().getConfig()->gameplay.characters.at(0).jumpkick;
}

void GraphicsComponent::setCharacterCrouchSprites(){
    _walk_sprites_path = Game::->getInstance().getConfig()->gameplay.characters.at(0).crouch;
}

void GraphicsComponent::setCharacterNeutralSprites(){
    _walk_sprites_path = Game::->getInstance().getConfig()->gameplay.characters.at(0).stand;
}

void GraphicsComponent::setEnemyWalkSprites(){
    _walk_sprites_path = Game::->getInstance().getConfig()->gameplay.npcs.at(0).walk;
}

void GraphicsComponent::setBarrelNeutralSprites(){
    _walk_sprites_path = Game::->getInstance().getConfig()->gameplay.utilities.barrel;
}

void GraphicsComponent::setBoxNeutralSprites(){
    _walk_sprites_path = Game::->getInstance().getConfig()->gameplay.utilities.box;
}

void GraphicsComponent::setTubeNeutralSprites(){
    _walk_sprites_path = Game::->getInstance().getConfig()->gameplay.weapons.tube;
}

void GraphicsComponent::setKnifeNeutralSprites(){
    _walk_sprites_path = Game::->getInstance().getConfig()->gameplay.weapons.knife;
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

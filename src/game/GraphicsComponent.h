#ifndef GAME_GRAPHICSCOMPONENT_H
#define GAME_GRAPHICSCOMPONENT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <string>

#include "GameObjectType.h"
#include "PhysicsComponent.h"
#include "Action.h"

class GraphicsComponent : public Component {

private:
    GameObjectType _type = UNDEFINED; 

    std::string _walk_sprites_path;
    std::string _jump_sprites_path;
    std::string _punch_sprites_path;
    std::string _kick_sprites_path;
    std::string _jump_kick_sprites_path;
    std::string _crouch_sprites_path;
    std::string _neutral_sprites_path;

    std::vector<std::string> _background_floor_sprites_paths;
    std::vector<std::string> _background_middle_sprites_paths;
    std::vector<std::string> _background_far_sprites_paths;
    std::vector<std::string> _background_overlay_sprites_paths;

    std::string _current_sprites_path;
    std::vector<std::string> _current_background_sprites_paths;
    SDL_Texture *_currentSprite = nullptr;

    SDL_Rect _sourceRect;
    SDL_Rect _destinationRect;
    SDL_Renderer* _renderer = nullptr;

    Action _action = NONE;
    int _actionCounter = 0;
    bool _fliped = false;

    int _imageAmount = 1; //NO DEBERIA ESTA HARDCODEADO. DEBERIA DEPENDER DE LA ACTION

    PhysicsComponent* _physicsComponent = nullptr;

public:
    GraphicsComponent(int width, int height, PhysicsComponent* physicsComponent);
    ~GraphicsComponent();

    void update() override;
    void render() override;

    void setPosition(int x, int y);
    void setType(GameObjectType gameObjectType);

protected:
    void switchAction(Action action) override;
    void setSpritesAcordingToType();

private:
    void updatePosition();
    void loadSprite();
    void loadNextImage();

    bool notFliped();
    void flip();

    void setCharacterWalkSprites();
    void setCharacterJumpSprites();
    void setCharacterPunchSprites();
    void setCharacterKickSprites();
    void setCharacterJumpKickSprites();
    void setCharacterCrouchSprites();
    void setCharacterNeutralSprites();
    /*
    void setEnemyWalkSprites();
    void setBarrelNeutralSprites();
    void setBoxNeutralSprites();
    void setTubeNeutralSprites();
    void setKnifeNeutralSprites();
    void setBackgroundFloorSprites();
    void setBackgroundMiddleSprites();
    void setBackgroundFarSprites();
    void setBackgroundOverlaySprites();
    */

};

#endif //GAME_GRAPHICSCOMPONENT_H
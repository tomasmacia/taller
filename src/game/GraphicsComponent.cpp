#include "GraphicsComponent.h"
#include "TextureManager.h"

GraphicsComponent::GraphicsComponent(const char* textureFile){
    texture = TextureManager::loadTexture(textureFile);
}
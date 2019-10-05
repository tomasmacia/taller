#include "events.h"
#include <iostream>
#include <SDL2/SDL.h>
#include "character.h"
/* Funcionales son los movimientos (no laterales)
con las flechas, saltar con LCTRL, golpear con X y agacharse con Z*/

map<SDL_Scancode,binding>* Events::hotkeys;

bool Events::keyboard_event() {
    execute_event();
    if (SDL_PollEvent(&_event)) {
        binding b = getBindingForKeyPress(_event.key.keysym.scancode);
        switch (_event.type) {
            /*Click en la X*/
            case SDL_QUIT:
                LogManager::logDebug("Click en CERRAR (X)");
                return true;
            case SDL_KEYDOWN:
                switch (b) {
                    case(QUIT):
                        /*Aprete escape*/
                        LogManager::logDebug("ESCAPE presionado");
                        return  true;
                    case LEFT:
                        left =true;
                        _cody->setFlip(SDL_FLIP_HORIZONTAL);
                        LogManager::logDebug("IZQUIERDA PRESIONA");
                        return false;
                    case RIGHT:
                        rigth = true;
                        _cody->setFlip(SDL_FLIP_NONE);
                        LogManager::logDebug("DERECHA PRESIONA");
                        // solo me interesa la derecha
                        return false;
                    case UP:
                        up = true;
                        LogManager::logDebug("ARRIBA PRESIONA");
                        return false;
                    case DOWN:
                        down = true;
                        LogManager::logDebug("ABAJO PRESIONA");
                        return false;
                    case JUMP:
                        //Aviso si se presiona rigth o left antes de saltar
                        if (rigth){_cody->mov_jump(0);}
                        if (left) {_cody->mov_jump(1);}
                        _cody->move(1,-1);
                        LogManager::logDebug("SALTO PRESIONA");
                        return false;
                    case PUNCH:
                        _cody->move(2,-1);
                        LogManager::logInfo("PUÑO PRESIONA");
                        return false;
                    case CROUCH:
                        _cody->move(3,-1);
                        LogManager::logDebug("AGACHA PRESIONA");
                        return false;
                    case JUMP_KICK:
                        //Aviso si se presiona rigth o left antes de salta
                        if (rigth){ _cody->mov_jump(0);}
                        if (left) {_cody->mov_jump(1);}
                        _cody->move(5,-1);
                        LogManager::logDebug("SALTO CON PATADA PRESIONA");
                        return false;
                    case KICK:
                        _cody->move(6,-1);
                        LogManager::logInfo("PATADA PRESIONA");
                        return false;
                    default:
                        return false;
                }
            case SDL_KEYUP:
                switch (b) {
                    case LEFT:
                        left = false;
                        LogManager::logDebug("IZQUIERDA SUELTA");
                        return false;
                    case RIGHT:
                        rigth = false;
                        LogManager::logDebug("DERECHA SUELTA");
                        return false;
                    case UP:
                        up = false;
                        LogManager::logDebug("ARRIBA SUELTA");
                        return false;
                    case DOWN:
                        down = false;
                        LogManager::logDebug("ABAJO SUELTA");
                        return false;
                    case PUNCH:
                        return false;
                        LogManager::logDebug("PUÑO SUELTA");
                    case JUMP:
                        return false;
                        LogManager::logDebug("SALTO SUELTA");
                    default:
                        return false;
                }
        }
        return false;
    }
    return false;
};


void Events::execute_event(){
 
  
    if (up){_cody->move(0,8);}
    if (rigth) {_cody->move(0,6);}
    if (left){_cody->move(0,4);}
    if(down){_cody->move(0,2);}
}

binding Events::getBindingForKeyPress(SDL_Scancode scancode){
    try{
        return Events::hotkeys->at(scancode);
    } catch (const std::out_of_range){
        return NONE;
    }
}

void Events::addHotkey(SDL_Scancode scancode, binding b){
    Events::hotkeys->insert(std::make_pair(scancode,b));
}

void Events::initHotkeys(){
    Events::hotkeys = new map<SDL_Scancode,binding>;
}
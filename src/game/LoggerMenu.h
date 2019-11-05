#ifndef LOGGERMENU_H
#define LOGGERMENU_H

#include <utility>
#include<iostream>
#include<string>
#include <map>
#include <iomanip>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "../parser/CLIArgumentParser.h"
#include "../parser/config/config.h"
#include "../parser/xmlparser.h"
#include "../LogLib/LogManager.h"
#include "../net/Client.h"
#include "GameClient.h"


class LoggerMenu {
typedef std::pair<std::string, std::string> componente;
public:

    LoggerMenu(Client* client);
    bool open();
private:
    void setPositionToText();
    void OnEvent(SDL_Event* Event);
    void Nombre_de_Usuario_Estatico();
    void render();
    void Fondo();
    void Update();
    void initSDL();
    void destroy();
    void ValidarCredenciales();
    void cursorBlip();
    void MensajeEmergente(std::string path);
    void serverAcknowledge(MessageId id);


    void init();
    void close();
    void processResponse();


private:
    std::map<std::string, std::string> directorio;
    SDL_Texture* _texture = nullptr;
    SDL_Rect _usuario, _pass;
    int wi=800,he=600;
    SDL_Renderer* _render;
    SDL_Window *window = nullptr;
    SDL_Texture* Usuario=nullptr, *Usuario_completo=nullptr;
    SDL_Texture* pass =nullptr;
    bool succesfulLogin=false, cursosrInTxt=false, running=true;

    string inputed_password;
    bool waitingForServerAknowledge = false;
    
    std::string input,user,password;
    TTF_Font *font;
    SDL_Surface *message;
    SDL_Texture *text = nullptr;
    SDL_Color textColor;
    SDL_Rect textRect,UserRect;

    //cursor
    int enter, cursor;
    SDL_Rect destCursor;
    SDL_Texture* _cursor=nullptr;
    
    //Mesajes emergentes
    SDL_Texture* msjEmergente = nullptr;
    SDL_Rect msjEmrgnte;

    //Cliente
    Client* client_ = nullptr;
    MessageId response;
    bool serverAcknowledgeReceived = false;
    
};

#endif //LOGGERMENU_H
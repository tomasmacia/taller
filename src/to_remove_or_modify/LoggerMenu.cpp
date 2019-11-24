#include "LoggerMenu.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "../game/Game.h"
#include<string>

LoggerMenu::LoggerMenu(Client* client, GameClient* gameClient){
    this->client_ = client;
    this->gameClient = gameClient;
    enter = 0;
    cursor = 0;
}

void LoggerMenu::initSDL() {
    if( SDL_Init(SDL_INIT_VIDEO) == 0 ) {
        if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
            LogManager::logError("[LOGIN]: Fallo SDL_Image");
        }

        int windowWidth = 800;
        int windowHeight = 600;

        this->window = SDL_CreateWindow("Final Fight", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_HIDDEN);
        this->_render = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_PRESENTVSYNC);

        TTF_Init();
    }
    

}

void LoggerMenu::setPositionToText(){
    UserRect.x=475;
    UserRect.y=180;
    textRect.x=475;
    textRect.y=180;
}


void LoggerMenu::init(){
    initSDL();
    Fondo();
    setPositionToText();
    SDL_ShowWindow(window);
}

void LoggerMenu::close(){
    destroy();
}


void LoggerMenu::open() {

    init();
    LogManager::logInfo("[LOGIN]: abriendo ventana de login");
    SDL_Event Event;
    while(!succesfulLogin && running){

        while(SDL_PollEvent(&Event)){
            OnEvent(&Event);
        }

        if (serverAcknowledgeReceived){
            processResponse();
        }

        Update();
    }

    close();
}

void LoggerMenu::processResponse(){

    if (response == SUCCESS){
        MensajeEmergente("User y Passwors Aceptados");
        LogManager::logInfo("[LOGIN]: User y Passwors Aceptados");
        succesfulLogin = true;
        gameClient->setLogged();
    }
    if (response == INVALID_CREDENTIAL){
        MensajeEmergente("User y Passwors no existentes");
        LogManager::logInfo("[LOGIN]: User y Passwors no existentes");
    }
    if (response ==ALREADY_LOGGED_IN_CREDENTIAL){
        MensajeEmergente("User ya logeado");
        LogManager::logInfo("[LOGIN]: User ya logeado");
    }
    if (response ==SERVER_FULL){
        MensajeEmergente("Server Completo");
        LogManager::logInfo("[LOGIN]: Server Completo");
    }
    serverAcknowledgeReceived = false;
    waitingForServerAknowledge = false;
}


void LoggerMenu::Fondo(){
    SDL_Surface*_image = IMG_Load("resources/sprites/Menu/logo.png");
    _texture = SDL_CreateTextureFromSurface( _render, _image );
    SDL_FreeSurface(_image);

    int w=0,h=0;
    font =TTF_OpenFont("resources/sprites/Menu/reve.ttf",20);
    textColor.r=textColor.g=textColor.b=0;

    _image = TTF_RenderText_Solid(font,"User: ",textColor);
    Usuario= SDL_CreateTextureFromSurface(_render,_image);
    SDL_QueryTexture(Usuario,NULL,NULL,&w,&h);
    _usuario.x=550;_usuario.y=150;
    _usuario.h=h;_usuario.w=w;
    SDL_FreeSurface(_image);

    _image = TTF_RenderText_Solid(font,"Password: ",textColor);
    pass= SDL_CreateTextureFromSurface(_render,_image);
    SDL_QueryTexture(pass,NULL,NULL,&w,&h);
    _pass.x=525;_pass.y=250;
    _pass.h=h;_pass.w=w;
    SDL_FreeSurface(_image);

    _image = TTF_RenderText_Solid(font,"l",textColor);
    _cursor= SDL_CreateTextureFromSurface(_render,_image);
    SDL_QueryTexture(_cursor,NULL,NULL,&w,&h);
    destCursor.x=475;destCursor.y=180;
    destCursor.h=h;destCursor.w=w;
    SDL_FreeSurface(_image);

}


void LoggerMenu::Update(){
    cursorBlip();
    SDL_RenderClear(_render);
    SDL_RenderCopy( _render, _texture, NULL, NULL );
    SDL_RenderCopy(_render,Usuario,NULL,&_usuario);
    SDL_RenderCopy(_render,pass,NULL,&_pass);
    if(text!=nullptr){
      SDL_RenderCopy(_render, text, NULL, &textRect);
    }
    if(Usuario_completo!=nullptr){
        SDL_RenderCopy(_render, Usuario_completo, NULL, &UserRect);
    }
    if(msjEmergente!=nullptr){
        SDL_RenderCopy(_render,msjEmergente, NULL, &msjEmrgnte);
    }
    if(cursosrInTxt){
      SDL_RenderCopy(_render,_cursor, NULL, &destCursor);
    }
    SDL_RenderPresent(_render);


}

void LoggerMenu::destroy() {
    SDL_DestroyTexture(_texture);
    SDL_DestroyTexture(Usuario);
    SDL_DestroyTexture(pass);
    SDL_DestroyTexture(text);
    SDL_DestroyTexture(Usuario_completo);
    SDL_DestroyTexture(msjEmergente);
    SDL_DestroyTexture(_cursor);
    SDL_DestroyWindow(this->window);
    SDL_DestroyRenderer(this->_render);
    TTF_CloseFont(font);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

}


void LoggerMenu::cursorBlip(){
    if (cursor ==30) {
        cursosrInTxt=(!cursosrInTxt);
        cursor=0;
    }
    cursor++;

}


void LoggerMenu::OnEvent(SDL_Event* Event) {
    //handle window close
    if(Event->type == SDL_QUIT) {
        running = false;
        gameClient->end();
    }

    //handle key press
    if(Event->type == SDL_KEYDOWN) {
        switch(Event->key.keysym.sym) {
            case SDLK_TAB:break;
            case SDLK_LSHIFT:break;
            case SDLK_RSHIFT:break;
            case SDLK_SPACE:break;
            case SDLK_LALT:break;
            case SDLK_RALT:break;
            case SDLK_LCTRL:break;
            case SDLK_RCTRL:break;
            case SDLK_UP:break;
            case SDLK_DOWN:break;
            case SDLK_LEFT:break;
            case SDLK_RIGHT:break;
            case SDLK_KP_DIVIDE:break; 
            case SDLK_KP_MULTIPLY:break;
            case SDLK_KP_0:break;
            case SDLK_KP_1:break;
            case SDLK_KP_2:break;
            case SDLK_KP_3:break;
            case SDLK_KP_4:break;
            case SDLK_KP_5:break;
            case SDLK_KP_6:break;
            case SDLK_KP_7:break;
            case SDLK_KP_8:break;
            case SDLK_KP_9:break;
            case SDLK_KP_MINUS:break;
            case SDLK_KP_PLUS:break;
            case SDLK_RETURN:

                if (!waitingForServerAknowledge){

                    if (enter == 1){
                        enter=0;
                        textRect.y = 180;
                        inputed_password = input;

                        if (user != "" && inputed_password != ""){
                            gameClient->setPlayerName(user);
                            ValidarCredenciales();
                        }
                        else{
                            MensajeEmergente("Se dejaron campos vacios");
                            LogManager::logInfo("[LOGIN]: Se dejaron campos vacios");
                        }
                    }
                    else
                    {
                        enter++;
                        user=input;
                        input.clear();
                        Nombre_de_Usuario_Estatico();
                        textRect.y = 280;

                    }
                    destCursor.x = textRect.x;
                    destCursor.y = textRect.y;
                }
                break;
            
            case SDLK_BACKSPACE:
              if (!input.empty()){
                  input.pop_back();
                  if (!password.empty()){
                    password.pop_back();
                  }
                  this->render();
                }
              break;
            case SDLK_ESCAPE:
              //running=false;
                //gameClient->end();
              break;
            default:
            //Solo 10 caracteres para no salirse de su espacio
              if(input.size()<10){
                input = input + SDL_GetScancodeName(Event->key.keysym.scancode);
                if (enter ==1){
                   password += "*";
                }
                this->render();
              }
              break;
        }
    }
}

void LoggerMenu::Nombre_de_Usuario_Estatico(){
    message = TTF_RenderText_Solid( font, user.c_str(), textColor );
    Usuario_completo = SDL_CreateTextureFromSurface(_render,message);
    UserRect.h=textRect.h;
    UserRect.w=textRect.w;
    SDL_DestroyTexture(text);
    text=nullptr;
    SDL_FreeSurface(message);

}

void LoggerMenu::ValidarCredenciales() {

    client_->sendCredentials(user,inputed_password);

    waitingForServerAknowledge = true;
    MensajeEmergente("Esperando respuesta del server");
    LogManager::logInfo("[LOGIN]: Esperando respuesta del server");

    SDL_DestroyTexture(text);
    SDL_DestroyTexture(Usuario_completo);
    Usuario_completo=nullptr;
    text=nullptr;
    user.clear();
    password.clear();
    input.clear();
}


void LoggerMenu::render(){
    int w=0,h=0;
    SDL_DestroyTexture(text);
    if (enter == 1) {
      message = TTF_RenderText_Solid( font, password.c_str(), textColor );
    }
    else {
      message = TTF_RenderText_Solid( font, input.c_str(), textColor );
    }
    text = SDL_CreateTextureFromSurface(_render,message);
    SDL_QueryTexture(text, NULL, NULL, &w, &h);
    textRect.w=w;textRect.h=h;
    destCursor.x=textRect.x + w;
    SDL_FreeSurface(message);
}


void LoggerMenu::MensajeEmergente(std::string path){
    SDL_DestroyTexture(msjEmergente);  
    int w=0,h=0;
    SDL_Surface* _image = TTF_RenderText_Solid(font,path.c_str(),textColor);
    msjEmergente= SDL_CreateTextureFromSurface(_render,_image);
    SDL_QueryTexture(msjEmergente,NULL,NULL,&w,&h);
    msjEmrgnte.x=475;msjEmrgnte.y=350;
    msjEmrgnte.h=h;msjEmrgnte.w=w;
    SDL_FreeSurface(_image);

}

void LoggerMenu::serverAcknowledge(MessageId ServerResponse){
    response = ServerResponse;
    serverAcknowledgeReceived = true;
}
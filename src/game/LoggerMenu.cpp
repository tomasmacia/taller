#include "LoggerMenu.h"
#include <SDL2/SDL_image.h>
#include "TextureWrapper.h"
#include "Game.h"
#include<iostream>
#include<string>

LoggerMenu::LoggerMenu(){
   // initSDL();
  agregar();
  enter = 0;
  cursor=0;
  initSDL();
}

void LoggerMenu::initSDL() {
    if( SDL_Init(SDL_INIT_VIDEO) == 0 ) {
        if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
            LogManager::logError("Fallo SDL_Image");
        }

        int windowWidth = 800;
        int windowHeight = 600;

        this->window = SDL_CreateWindow("Final Fight", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_HIDDEN);
        this->_render = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_PRESENTVSYNC);

        TTF_Init();
    }
    

}

void LoggerMenu::setPositionToText(){

  UserRect.x=475;UserRect.y=180;
  textRect.x=475;textRect.y=180;
}



void LoggerMenu::agregar()
{
    directorio.insert( componente ("BLANCA", "111") );
    directorio.insert( componente("OSCAR", "222"));
    directorio.insert( componente("TERESA", "333"));
    directorio.insert( componente("CARLOS", "444"));
    directorio.insert( componente("JUAN", "555"));
    directorio.insert( componente("RUBEN", "666"));
    directorio.insert( componente("ANDREA", "777"));
}

bool LoggerMenu::open(){
  Fondo();
  setPositionToText();
  SDL_ShowWindow(window);
  SDL_Event Event;
    while(running){
      while(SDL_PollEvent(&Event)){ 
        OnEvent(&Event);
      }
      Update();
    }
  SDL_Delay(1000);
  this->destroy();
  if (quit){
    return false;
  }
  return true;
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

  void LoggerMenu::destroy(){
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
  if (cursor ==30){
    cursosrInTxt=(!cursosrInTxt);
    cursor=0;
  }
  cursor++;

}
void LoggerMenu::OnEvent(SDL_Event* Event) {
    //handle window close
    if(Event->type == SDL_QUIT) {
        quit = true;
        running = false;
    }

    //handle key press
    if(Event->type == SDL_KEYDOWN)
    {
        switch(Event->key.keysym.sym)
        {
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
              if (enter == 1){
                enter=0;
                textRect.y = 180;
                ValidarCredenciales();
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
              break;
            
            case SDLK_BACKSPACE:
              if (!input.empty()){
                  input.pop_back();
                  this->typing();
                }
              break;
            case SDLK_ESCAPE:
              quit = true;
              running=false;
              break;
            default:
            //Solo 10 caracteres para no salirse de su espacio
              if(input.size()<10){
                input = input + SDL_GetScancodeName(Event->key.keysym.scancode);
                this->typing();
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

void LoggerMenu::ValidarCredenciales(){
  
  std::map<std::string, std::string>::iterator p = directorio.find(user);
  if(p != directorio.end()){
    if(p->second == input){
      MensajeEmergente("User y Password aceptados");
        LogManager::logInfo("User y Password aceptados");
      running=false;
    }
    else{
      MensajeEmergente("Password incorrecto");
      LogManager::logError("Password incorrecto");
    }
  }
  else {
    MensajeEmergente("Usuario no existente");
    LogManager::logError("Usuario no existente");
  }

  SDL_DestroyTexture(text);
  SDL_DestroyTexture(Usuario_completo);
  Usuario_completo=nullptr;
  text=nullptr;
  user.clear();
  password.clear();
  input.clear();
}

void LoggerMenu::typing(){
    int w=0,h=0;
    SDL_DestroyTexture(text);
    if (enter == 1){
      password += "*";
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
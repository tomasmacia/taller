#ifndef WINDOW_H_
#define WINDOW_H_
#include <SDL2/SDL.h>
#include "iostream" 


class Window{
    
private:
 //   ImageManager* _imagemanager;
    std::string _title;
    int _width;
    int _height;


public:
    Window(const std::string &title, int width,int height);
    ~Window();
    void loadpj(const std::string &rute, SDL_Rect r);
    void updateWindow();    
    SDL_Window *_window = nullptr;
private:
    bool init();
    void raiseException();
    
};

#endif

#include <string>
#include "iostream"
#include <SDL2/SDL.h> 
#include "imageManager.h"

class Window{

public:
    static SDL_Renderer *_renderer;
    
private:
    ImageManager* _imagemanager;
    std::string _title;
    int _width;
    int _height;
    SDL_Window *_window = nullptr;

public:
    Window(const std::string &title, int width,int height);
    ~Window();
    void display();
    void loadpj(const std::string &rute, SDL_Rect r);
    void frame_load(SDL_Rect position);
private:
    bool init();
    void raiseException();
    
};

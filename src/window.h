#include <string>
#include "iostream"
#include <SDL2/SDL.h> 




class Window{

public:
    static SDL_Renderer *_renderer;
    
private:
    std::string _title;
    int _width;
    int _height;
    
    SDL_Window *_window = nullptr;

public:
    Window(const std::string &title, int width,int height);
    ~Window();
    void display();
    void loadMedia();

private:
    bool init();
    void raiseException();
};

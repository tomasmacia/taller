#include <string>
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

private:
    bool init();
    void raiseException();
};

#include <string>
#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h>

class Window{
    
private:
    std::string _title;
    int _width;
    int _height;
    bool _closed = false;
    
    SDL_Window *_window = nullptr;
    SDL_Renderer* _renderer = nullptr;
    SDL_Texture* _Texture = nullptr;

public:
    Window(const std::string title, int width,int height);
    ~Window();

    bool isClosed();
    void display();
    SDL_Renderer* getRenderer();
    void close();
    void showAll();

private:
    bool init();
    void raiseException(std::string mesage);
};
#include <string>
#include <SDL2/SDL.h>  

class Window{
public:
    Window(const std::string &title, int width,int height);
    ~Window();

    bool isClosed();
    void poolEvents();

private:
    bool init();
    void raiseException();

private:
    std::string _title;
    int _width;
    int _height;


    bool _closed = false;

    SDL_Window *_window = nullptr;
};
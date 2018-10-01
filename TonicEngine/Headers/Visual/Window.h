#ifndef PROJECT_SWA_WINDOW_H
#define PROJECT_SWA_WINDOW_H
#include <string>
#include <SDL2/SDL.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

class Window {
public:
    Window(const std::string &title, int width, int height);
    ~Window();

    void pollEvents();
    inline bool isClosed() const { return _closed; };

private:
    bool init();

private:
    std::string _title;
    int _width = SCREEN_WIDTH;
    int _height = SCREEN_HEIGHT;

    bool _closed = false;

    SDL_Window *_window = nullptr;
};


#endif //PROJECT_SWA_WINDOW_H

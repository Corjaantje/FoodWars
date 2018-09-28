#ifndef PROJECT_SWA_WINDOW_H
#define PROJECT_SWA_WINDOW_H
#include <string>
#include <SDL2/SDL.h>

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
    int _width = 640;
    int _height = 480;

    bool _closed = false;

    SDL_Window *_window = nullptr;
};


#endif //PROJECT_SWA_WINDOW_H

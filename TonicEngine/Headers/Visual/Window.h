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

    bool createWindow();
    bool closeWindow();
    void setTitle(const std::string &title);
    void setResolution(int width, int height);
    bool setFullscreen(bool state);
    void pollEvents();
    inline bool isClosed() const { return _closed; };
    SDL_Renderer* getRenderer();
private:
    bool init();

private:
    std::string _title;
    int _width = SCREEN_WIDTH;
    int _height = SCREEN_HEIGHT;

    bool _closed = false;
    bool _fullscreen = false;
    SDL_Window *_window = nullptr;
    SDL_Renderer *_renderer = nullptr;
};


#endif //PROJECT_SWA_WINDOW_H

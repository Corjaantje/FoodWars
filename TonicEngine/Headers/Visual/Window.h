#ifndef PROJECT_SWA_WINDOW_H
#define PROJECT_SWA_WINDOW_H
#include <string>
#include <SDL2/SDL.h>

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
    int _width;
    int _height;

    bool _closed = false;
    bool _fullscreen = false;
    SDL_Window *_window = nullptr;
    SDL_Renderer *_renderer = nullptr;
};


#endif //PROJECT_SWA_WINDOW_H

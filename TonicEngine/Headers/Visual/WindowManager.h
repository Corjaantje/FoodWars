#ifndef PROJECT_SWA_VISUALMANAGER_H
#define PROJECT_SWA_VISUALMANAGER_H

#include <string>
#include "Window.h"
#include "ShapeRectangle.h"
#include "ShapeSprite.h"
#include <vector>

class WindowManager {
public:
    WindowManager();
    ~WindowManager();

    void render();

    void setTitle(const std::string &title);
    void setResolution(int width, int height);

    void openWindow();
    void closeWindow();

    void enableFullscreen();
    void disablefullscreen();

    void pollEvents();
    bool isWindowClosed();

public:
    std::vector<ShapeRectangle> _rectangleList;
    std::vector<ShapeSprite> _spriteList;

private:
    void renderRectangles();
    void renderSprites();

private:
    Window *_window = nullptr;
    SDL_Renderer *_renderer = nullptr;
    std::string _title = "Default Title";
    int _windowHeight = 480;
    int _windowWidth = 640;
    bool _fullscreen = false;
};


#endif //PROJECT_SWA_VISUALMANAGER_H

#ifndef PROJECT_SWA_VISUALFACADE_H
#define PROJECT_SWA_VISUALFACADE_H

#include <string>
#include <SDL2/SDL.h>

#include "Window.h"
#include "WindowManager.h"

class VisualFacade {
public:
    VisualFacade();
    ~VisualFacade();

    void render();

    void setTitle(const std::string &title);
    void setResolution(int width, int height);

    void openWindow();
    void closeWindow();

    void enableFullscreen();
    void disablefullscreen();

    bool setBackground();
    bool removeBackground();

    bool addSprite(ShapeSprite sprite);
    bool removeSprite();
    bool updateSprite();

    bool addRectangle(ShapeRectangle rectangle);
    bool removeRectangle();
    bool updateRectangle();

    bool addCircle();
    bool removeCircle();
    bool updateCircle();

    void pollEvents();
    bool isWindowClosed();
private:
    bool init();
public:
    WindowManager *_windowManager = nullptr;
};


#endif //PROJECT_SWA_VISUALFACADE_H

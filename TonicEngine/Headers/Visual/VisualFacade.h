#ifndef PROJECT_SWA_VISUALFACADE_H
#define PROJECT_SWA_VISUALFACADE_H

#include <string>
#include <SDL2/SDL.h>
#include "Window.h"

class VisualFacade {
public:
    VisualFacade();
    ~VisualFacade();

    bool render();

    void setTitle(const std::string &title);
    void setResolution(const int height, const int width);

    void enableFullscreen();
    void disablefullscreen();

    bool setBackground();
    bool removeBackground();

    bool addSprite();
    bool removeSprite();
    bool updateSprite();

    bool addRectangle();
    bool removeRectangle();
    bool updateRectangle();

    bool addCircle();
    bool removeCircle();
    bool updateCircle();
private:
    bool init();
};


#endif //PROJECT_SWA_VISUALFACADE_H

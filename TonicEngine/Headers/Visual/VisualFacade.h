#ifndef PROJECT_SWA_VISUALFACADE_H
#define PROJECT_SWA_VISUALFACADE_H

#include <string>
#include <SDL2/SDL.h>

#include "Window.h"
#include "WindowManager.h"
#include "../../Facades/IFacade.h"
#include "../General/WindowResolutionCalculator.h"

class VisualFacade : public IFacade {
public:
    VisualFacade();
    ~VisualFacade();

    void render(Renderlist renderlist);

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

    WindowResolutionCalculator* getWindowResCalc();

    void pollEvents();
    bool isWindowClosed();
private:
    bool init();
public:
    WindowManager *_windowManager = nullptr;
    WindowResolutionCalculator *_windowResCalc = nullptr;
};


#endif //PROJECT_SWA_VISUALFACADE_H

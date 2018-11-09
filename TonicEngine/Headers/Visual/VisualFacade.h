#ifndef PROJECT_SWA_VISUALFACADE_H
#define PROJECT_SWA_VISUALFACADE_H

#include <string>
#include <SDL2/SDL.h>

#include "Window.h"
#include "WindowManager.h"
#include "../../Facades/IFacade.h"

class VisualFacade : public IFacade {
public:
    VisualFacade(std::shared_ptr<WindowResolutionCalculator> windowResolutionCalculator);
    ~VisualFacade();

    void render(Renderlist renderlist);

    void setTitle(const std::string &title);
    void setResolution(int width, int height);
    int getWindowWidth() const;
    int getWindowHeight() const;

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
    WindowManager *_windowManager = nullptr;
    std::shared_ptr<WindowResolutionCalculator> _windowResCalc = nullptr;
};


#endif //PROJECT_SWA_VISUALFACADE_H

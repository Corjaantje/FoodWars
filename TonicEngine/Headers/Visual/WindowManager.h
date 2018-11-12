#ifndef PROJECT_SWA_VISUALMANAGER_H
#define PROJECT_SWA_VISUALMANAGER_H

#include <string>
#include "Window.h"
#include "Shapes/ShapeRectangle.h"
#include "Shapes/ShapeSprite.h"
#include "Renderlist.h"
#include "AssetManager.h"
#include "../General/WindowResolutionCalculator.h"
#include <vector>
#include <memory>

class WindowManager {
public:
    WindowManager(std::shared_ptr<WindowResolutionCalculator> windowResCalc);
    ~WindowManager();

    void render(Renderlist renderlist);

    void setTitle(const std::string &title);
    void setResolution(int width, int height);
    int getWindowWidth() const;
    int getWindowHeight() const;

    void openWindow();
    void closeWindow();

    void enableFullscreen();
    void disablefullscreen();

    void pollEvents();
    bool isWindowClosed();

private:
    void renderRectangles(std::vector<ShapeRectangle> rectangleList);
    void renderSprites(std::vector<ShapeSprite> rectangleSprite);
    void renderText(std::vector<ShapeText> textList);

private:
    AssetManager* _assetManager = nullptr;
    Window *_window = nullptr;
    SDL_Renderer *_renderer = nullptr;
    std::shared_ptr<WindowResolutionCalculator> _windowResCalc = nullptr;
    std::string _title = "Default Title";
    int _windowHeight = DEFAULT_HEIGHT;
    int _windowWidth = DEFAULT_WIDTH;
    bool _fullscreen = false;
};


#endif //PROJECT_SWA_VISUALMANAGER_H

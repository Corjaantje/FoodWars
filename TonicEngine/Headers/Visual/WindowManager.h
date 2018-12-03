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
#include "IRenderer.h"

class WindowManager : public IRenderer {
public:
    WindowManager(WindowResolutionCalculator& windowResCalc);
    ~WindowManager();

    void render(Renderlist &renderlist);

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

    void renderRectangle(const ShapeRectangle &rectangle) override;
    void renderText(const ShapeText &text) override;
    void renderSprite(const ShapeSprite &sprite) override;
    void renderLine(const ShapeLine &line) override;

private:
    AssetManager* _assetManager = nullptr;
    Window *_window = nullptr;
    SDL_Renderer *_renderer = nullptr;
    WindowResolutionCalculator* _windowResCalc = nullptr;
    std::string _title = "Default Title";
    int _windowHeight = DEFAULT_HEIGHT;
    int _windowWidth = DEFAULT_WIDTH;
    bool _fullscreen = false;
};


#endif //PROJECT_SWA_VISUALMANAGER_H

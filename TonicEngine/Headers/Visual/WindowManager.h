#ifndef PROJECT_SWA_VISUALMANAGER_H
#define PROJECT_SWA_VISUALMANAGER_H

#include <string>
#include "Window.h"
#include "Shapes/ShapeRectangle.h"
#include "Shapes/ShapeSprite.h"
#include "Renderlist.h"
#include "TextureManager.h"
#include "FontManager.h"
#include <vector>

class WindowManager {
public:
    WindowManager();
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
    TextureManager _textureManager;
    FontManager _fontManager;
    Window *_window = nullptr;
    SDL_Renderer *_renderer = nullptr;
    std::string _title = "Default Title";
    int _windowHeight = 480;
    int _windowWidth = 640;
    bool _fullscreen = false;
};


#endif //PROJECT_SWA_VISUALMANAGER_H

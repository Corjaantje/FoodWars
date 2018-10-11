#include "../../Headers/Visual/WindowManager.h"
#include "../../Headers/Visual/Window.h"
#include <SDL2/SDL.h>

WindowManager::WindowManager() {
    _window = new Window(_title, _windowWidth, _windowHeight);
}

WindowManager::~WindowManager() {
    closeWindow();
    delete _window;
}

void WindowManager::openWindow(){
    _window->createWindow();
}

void WindowManager::closeWindow(){
    _window->closeWindow();
};

void WindowManager::setTitle(const std::string &title){
    _title = title;
    updateWindowSettings();
};

void WindowManager::setResolution(int width, int height){
    _windowHeight = height;
    _windowWidth = width;
    updateWindowSettings();
};

void WindowManager::enableFullscreen(){
    _fullscreen = true;
    updateWindowSettings();
};

void WindowManager::disablefullscreen(){
    _fullscreen = false;
    updateWindowSettings();
};

//TODO Change this to update the window, not replace it if possible!
void WindowManager::updateWindowSettings() {
    delete _window;
    _window = new Window(_title, _windowWidth, _windowHeight);
    _window->setFullscreen(_fullscreen);
}

//(re)Draw all the shapes, sprites etc. that are added to the WindowManager
void WindowManager::render() {
    SDL_RenderClear(_renderer);
    _renderer = _window->getRenderer();
    renderRectangles();
    renderSprites();
    SDL_RenderPresent(_renderer);
}

void WindowManager::renderRectangles() {
    for(int i=0; i< _rectangleList.size(); i++){
        ShapeRectangle &rectangleShape = _rectangleList[i];
        SDL_Rect rect;
        rect.x = rectangleShape.xPos;
        rect.y = rectangleShape.yPos;
        rect.h = rectangleShape.height;
        rect.w = rectangleShape.width;
        SDL_SetRenderDrawColor(_renderer, rectangleShape.colour.red, rectangleShape.colour.green, rectangleShape.colour.blue, rectangleShape.colour.alpha);
        SDL_RenderFillRect(_renderer, &rect);
    }
    SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 0);
}

//TODO This causes a massive memory leak at this point due to loading the Bitmap Image. We are aware of
//TODO the issue and will be fixed in a few days.
void WindowManager::renderSprites() {
    for(int i=0; i< _spriteList.size(); i++){
        ShapeSprite &shapeSprite = _spriteList[i];
        SDL_Rect rect;
        rect.x = shapeSprite.xPos;
        rect.y = shapeSprite.yPos;
        rect.h = shapeSprite.height;
        rect.w = shapeSprite.width;
        SDL_Surface * image = SDL_LoadBMP(shapeSprite.imageURL.c_str());
        SDL_Texture * texture = SDL_CreateTextureFromSurface(_renderer, image);
        SDL_RenderCopy(_renderer, texture, NULL, &rect);
    }
}

void WindowManager::pollEvents() {
    _window->pollEvents();
}

bool WindowManager::isWindowClosed() {
    return _window->isClosed();
}

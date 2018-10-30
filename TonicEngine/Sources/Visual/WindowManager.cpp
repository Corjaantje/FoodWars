#include "../../Headers/Visual/WindowManager.h"
#include "../../Headers/Visual/Window.h"
#include "../../Headers/Visual/TextureManager.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

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
    _window->setTitle(title);
};

void WindowManager::setResolution(int width, int height){
    _window->setResolution(width, height);

};

void WindowManager::enableFullscreen(){
    _fullscreen = true;
    _window->setFullscreen(true);
};

void WindowManager::disablefullscreen(){
    _fullscreen = false;
    _window->setFullscreen(false);
};

//(re)Draw all the shapes, sprites etc. that are added to the WindowManager
void WindowManager::render(Renderlist renderlist) {
    SDL_RenderClear(_renderer);
    _renderer = _window->getRenderer();
    renderRectangles(renderlist.rectangleList);
    renderSprites(renderlist.spriteList);
    renderText(renderlist.textList);
    SDL_RenderPresent(_renderer);
}

void WindowManager::renderRectangles(std::vector<ShapeRectangle> rectangleList) {
    for(int i=0; i< rectangleList.size(); i++){
        ShapeRectangle &rectangleShape = rectangleList[i];
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

void WindowManager::renderSprites(std::vector<ShapeSprite> rectangleSprite) {
    for(int i=0; i< rectangleSprite.size(); i++){
        ShapeSprite &shapeSprite = rectangleSprite[i];
        SDL_Rect rect;
        rect.x = shapeSprite.xPos;
        rect.y = shapeSprite.yPos;
        rect.h = shapeSprite.height;
        rect.w = shapeSprite.width;
        SDL_Texture* texture = _textureManager.GetSDLTextureFromPNG(_renderer, shapeSprite.imageURL);
        SDL_RenderCopy(_renderer, texture, NULL, &rect);
    }
}

void WindowManager::renderText(std::vector<ShapeText> textList) {
    for(int i=0; i< textList.size(); i++){
        ShapeText &shapeText = textList[i];
        SDL_Texture* Message = _fontManager.GetSDLTextureFromText(_renderer, shapeText);
        SDL_Rect Message_rect; //create a rect
        Message_rect.x = shapeText.xPos;  //controls the rect's x coordinate
        Message_rect.y = shapeText.yPos; // controls the rect's y coordinte
        Message_rect.w = shapeText.width; // controls the width of the rect
        Message_rect.h = shapeText.height; // controls the height of the rect
        SDL_RenderCopy(_renderer, Message, NULL, &Message_rect);
    }
}

void WindowManager::pollEvents() {
    _window->pollEvents();
}

bool WindowManager::isWindowClosed() {
    return _window->isClosed();
}

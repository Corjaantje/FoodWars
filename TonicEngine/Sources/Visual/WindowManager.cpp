#include <utility>

#include "../../Headers/Visual/WindowManager.h"
#include "../../Headers/Visual/Window.h"
#include "../../Headers/Visual/Shapes/ShapeLine.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <algorithm>
#include <iostream>

WindowManager::WindowManager(std::shared_ptr<WindowResolutionCalculator> windowResCalc) {
    _window = new Window(_title, _windowWidth, _windowHeight);
    _windowResCalc = std::move(windowResCalc);
    _assetManager = new AssetManager();
}

WindowManager::~WindowManager() {
    closeWindow();
    delete _window;
    delete _assetManager;
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
    _windowWidth = width;
    _windowHeight = height;
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
void WindowManager::render(Renderlist &renderlist) {
    SDL_RenderClear(_renderer);
    _renderer = _window->getRenderer();
    for (const auto &iterator: renderlist._shapes) {
        //std::cout <<  "render layer: " << iterator.first << std::endl;
        for (const IShape* shape : iterator.second) {
            shape->render(*this);
        }
    }
    SDL_RenderPresent(_renderer);
}

void WindowManager::pollEvents() {
    _window->pollEvents();
}

bool WindowManager::isWindowClosed() {
    return _window->isClosed();
}

void WindowManager::renderRectangle(const ShapeRectangle &rectangleShape) {
    SDL_Rect rect;
    rect.x = _windowResCalc->getConvertedxPosDraw(rectangleShape.xPos);
    rect.y = _windowResCalc->getConvertedyPosDraw(rectangleShape.yPos);
    rect.h = _windowResCalc->getConvertedHeightDraw(rectangleShape.height);
    rect.w = _windowResCalc->getConvertedWidthDraw(rectangleShape.width);
    SDL_SetRenderDrawColor(_renderer, rectangleShape.colour.red, rectangleShape.colour.green, rectangleShape.colour.blue, rectangleShape.colour.alpha);
    SDL_RenderFillRect(_renderer, &rect);
    SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 0);
}

void WindowManager::renderText(const ShapeText &shapeText) {
    SDL_Texture* Message = _assetManager->GetSDLTextureFromText(_renderer, shapeText);
    SDL_Rect Message_rect; //create a rect
    Message_rect.x = _windowResCalc->getConvertedxPosDraw(shapeText.xPos);  //controls the rect's x coordinate
    Message_rect.y = _windowResCalc->getConvertedyPosDraw(shapeText.yPos); // controls the rect's y coordinte
    Message_rect.w = _windowResCalc->getConvertedWidthDraw(shapeText.width);; // controls the width of the rect
    Message_rect.h = _windowResCalc->getConvertedHeightDraw(shapeText.height); // controls the height of the rect
    SDL_RenderCopy(_renderer, Message, nullptr, &Message_rect);
}

void WindowManager::renderSprite(const ShapeSprite &shapeSprite) {
    SDL_Rect rect;
    rect.x = _windowResCalc->getConvertedxPosDraw(shapeSprite.xPos);
    rect.y = _windowResCalc->getConvertedyPosDraw(shapeSprite.yPos);
    rect.h = _windowResCalc->getConvertedHeightDraw(shapeSprite.height);
    rect.w = _windowResCalc->getConvertedWidthDraw(shapeSprite.width);
    SDL_Texture* texture = _assetManager->GetSDLTextureFromPNG(_renderer, shapeSprite.imageURL);
    SDL_RenderCopy(_renderer, texture, nullptr, &rect);
}

void WindowManager::renderLine(const ShapeLine &line) {

    int x = _windowResCalc->getConvertedxPosDraw(line.xPos);
    int y = _windowResCalc->getConvertedyPosDraw(line.yPos);
    int x2 = _windowResCalc->getConvertedxPosDraw(line.xPos2);
    int y2 = _windowResCalc->getConvertedyPosDraw(line.yPos2);
    SDL_RenderDrawLine(_renderer, x, y, x2, y2);
}



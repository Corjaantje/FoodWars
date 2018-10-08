#include "../../Headers/Visual/VisualFacade.h"
#include "../../Headers/Visual/Window.h"

VisualFacade::VisualFacade() {
    VisualFacade::init();
}

VisualFacade::~VisualFacade() {
    delete _windowManager;
}

bool VisualFacade::init(){
    _windowManager = new WindowManager();
}

void VisualFacade::openWindow() {
    _windowManager->openWindow();
}

void VisualFacade::closeWindow() {
    _windowManager->closeWindow();
}

void VisualFacade::setTitle(const std::string &title){
    _windowManager->setTitle(title);
};

void VisualFacade::setResolution(int width, int height){
    _windowManager->setResolution(width, height);
};

void VisualFacade::enableFullscreen(){
    _windowManager->enableFullscreen();
};

void VisualFacade::disablefullscreen(){
    _windowManager->disablefullscreen();
};

void VisualFacade::render() {
    _windowManager->render();
}

bool VisualFacade::addRectangle(ShapeRectangle rectangle){
    _windowManager->_rectangleList.push_back(rectangle);
};

void VisualFacade::pollEvents() {
    _windowManager->pollEvents();
}

bool VisualFacade::isWindowClosed() {
    return _windowManager->isWindowClosed();
}

bool VisualFacade::addSprite(ShapeSprite sprite) {
    _windowManager->_spriteList.push_back(sprite);
}

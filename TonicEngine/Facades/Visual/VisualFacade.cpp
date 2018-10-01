#include "../../Headers/Visual/VisualFacade.h"
#include "../../Headers/Visual/Window.h"

VisualFacade::VisualFacade() {
    VisualFacade::init();
}

VisualFacade::~VisualFacade() {}

bool VisualFacade::render() {}

void VisualFacade::setTitle(const std::string &title) {

}

void VisualFacade::setResolution(const int height, const int width) {

}

void VisualFacade::enableFullscreen() {

}
void VisualFacade::disablefullscreen() {

}

bool VisualFacade::setBackground() {

}
bool VisualFacade::removeBackground() {

}

bool VisualFacade::addSprite() {}
bool VisualFacade::removeSprite() {}
bool VisualFacade::updateSprite() {}

bool VisualFacade::addRectangle() {}
bool VisualFacade::removeRectangle() {}
bool VisualFacade::updateRectangle() {}

bool VisualFacade::addCircle() {}
bool VisualFacade::removeCircle() {}
bool VisualFacade::updateCircle() {}

bool VisualFacade::init(){
    Window window = Window("SDL Window", 640, 480);

    while(!window.isClosed()){
        window.pollEvents();
    }
}
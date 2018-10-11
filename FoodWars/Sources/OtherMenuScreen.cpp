//
// Created by Lucas on 11/10/2018.
//

#include "../Headers/OtherMenuScreen.h"

void OtherMenuScreen::update(double deltaTime) const {
    visualFacade->pollEvents();
    visualFacade->render();
}

OtherMenuScreen::OtherMenuScreen(ScreenState *context) : IScreen(context) {
    visualFacade = context->getFacade<VisualFacade>();
    visualFacade->removeRectangle();
    visualFacade->addRectangle(ShapeRectangle{200, 200, 200, 200, Colour { 255, 255, 0, 100}});
}

OtherMenuScreen::~OtherMenuScreen() {

}
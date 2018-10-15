//
// Created by Lucas on 11/10/2018.
//

#include "../../Headers/StateMachine/OtherMenuScreen.h"

void OtherMenuScreen::update(double deltaTime) const {
    visualFacade->render(_renderList);
}

OtherMenuScreen::OtherMenuScreen(ScreenState *context) : IScreen(context) {
    visualFacade = context->getFacade<VisualFacade>();
    _renderList.rectangleList.emplace_back(ShapeRectangle{200, 200, 200, 200, Colour { 255, 255, 0, 100}});
}

OtherMenuScreen::~OtherMenuScreen() {

}
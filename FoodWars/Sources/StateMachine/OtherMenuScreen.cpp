//
// Created by Lucas on 11/10/2018.
//

#include "../../Headers/StateMachine/OtherMenuScreen.h"

void OtherMenuScreen::update(double deltaTime) const {
    visualFacade->render(_renderList);
    audioFacade->playMusic("wildwest");
}

OtherMenuScreen::OtherMenuScreen(std::shared_ptr<ScreenStateManager> context) : IScreen(context) {
    visualFacade = context->getFacade<VisualFacade>();
    _renderList.spriteList.emplace_back(640, 200, 0, 280, "../grass.bmp");
    audioFacade = context->getFacade<AudioFacade>();

}

OtherMenuScreen::~OtherMenuScreen() {

}
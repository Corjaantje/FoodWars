//
// Created by Lucas on 11/10/2018.
//

#include "../../Headers/StateMachine/MainMenuScreen.h"
#include "../../Headers/StateMachine/OtherMenuScreen.h"

void MainMenuScreen::update(double deltaTime) {
    visualFacade->render(_renderList);
}

MainMenuScreen::MainMenuScreen(std::shared_ptr<ScreenStateManager> context) : IScreen(context) {
    visualFacade = context->getFacade<VisualFacade>();
    _renderList.spriteList.emplace_back(200, 200, 50, 50, "../grass.bmp");

}

MainMenuScreen::~MainMenuScreen() {

}

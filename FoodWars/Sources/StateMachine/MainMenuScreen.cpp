//
// Created by Lucas on 11/10/2018.
//

#include "../../Headers/StateMachine/MainMenuScreen.h"
#include "../../Headers/StateMachine/OtherMenuScreen.h"

void MainMenuScreen::update(double deltaTime) const {
    visualFacade->render(_renderList);
    std::cout << deltaTime << std::endl;
    if(deltaTime > 100) {
        std::cout << "Change state " << std::endl;
        _context->setState(ScreenPtr{new OtherMenuScreen(_context)});
    }
}

MainMenuScreen::MainMenuScreen(ScreenState *context) : IScreen(context) {
    visualFacade = context->getFacade<VisualFacade>();
    _renderList.spriteList.emplace_back(200, 200, 50, 50, "../grass.bmp");

}

MainMenuScreen::~MainMenuScreen() {

}

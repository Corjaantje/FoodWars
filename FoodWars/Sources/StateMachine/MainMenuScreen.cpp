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
    for(int i=0; i < 1080; i++) {
        _renderList.rectangleList.emplace_back(i, 1, i, i, Colour{(i+125)%255, (i)%125, (i-100)%255, 100});
    }

}

MainMenuScreen::~MainMenuScreen() {

}

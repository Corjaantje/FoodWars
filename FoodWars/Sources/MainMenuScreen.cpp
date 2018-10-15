//
// Created by Lucas on 11/10/2018.
//

#include "../Headers/MainMenuScreen.h"
#include "../Headers/OtherMenuScreen.h"

void MainMenuScreen::update(double deltaTime) const {
    visualFacade->render();
    std::cout << deltaTime << std::endl;
    if(deltaTime > 100) {
        std::cout << "Change state " << std::endl;
        _context->setState(ScreenPtr{new OtherMenuScreen(_context)});
    }
}

MainMenuScreen::MainMenuScreen(ScreenState *context) : IScreen(context) {
    visualFacade = context->getFacade<VisualFacade>();
    if(visualFacade != nullptr) {
        visualFacade->addRectangle(ShapeRectangle{100,100,50,50, Colour {0, 0, 255, 100}});
    }
}

MainMenuScreen::~MainMenuScreen() {

}

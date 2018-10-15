#include "../../Headers/StateMachine/GameScreen.h"

GameScreen::GameScreen(std::shared_ptr<ScreenStateManager> context) : IScreen(context) {
    _visualFacade = context->getFacade<VisualFacade>();
    //Initialize the Entity Manager
    //Initialize the DrawSystem.
}

GameScreen::~GameScreen() {

}

void GameScreen::update(double deltaTime) {
    _drawSystem.update(deltaTime);
}
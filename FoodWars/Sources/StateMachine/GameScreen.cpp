#include "../../Headers/StateMachine/GameScreen.h"
#include "../../../TonicEngine/Headers/Input/InputFacade.h"

GameScreen::GameScreen(std::shared_ptr<ScreenStateManager> context) : IScreen(context),
        _entityManager(std::make_shared<EntityManager>()),
        _visualFacade(context->getFacade<VisualFacade>()),
        _drawSystem(_entityManager, _visualFacade),
        _inputFacade(context->getFacade<InputFacade>()),
        _inputSystem(std::make_shared<InputSystem>(_entityManager, _inputFacade)) {
    _inputFacade->getKeyEventObservable()->registerObserver(_inputSystem.get());
    //Initialize the Entity Manager
    //Initialize the DrawSystem.
}

GameScreen::~GameScreen() {
}

void GameScreen::update(double deltaTime) const {
    _drawSystem.update(deltaTime);
    _inputFacade->pollEvents();
}
#include "../../Headers/StateMachine/GameScreen.h"

GameScreen::GameScreen(std::shared_ptr<ScreenStateManager> context) : IScreen(context),
        _entityManager(std::make_shared<EntityManager>()),
        _visualFacade(context->getFacade<VisualFacade>()),
        _audioFacade(context->getFacade<AudioFacade>()),
        _drawSystem(_entityManager, _visualFacade),
        _inputFacade(context->getFacade<InputFacade>()),
        _inputSystem(std::make_shared<InputSystem>(_entityManager, _inputFacade)) {
        _inputFacade->getKeyEventObservable()->registerObserver(this);
    //Initialize the Entity Manager
    //Initialize the DrawSystem.
}

void GameScreen::update(std::shared_ptr<KeyEvent> event){
    if(event->getKey() == KEY::KEY_ESCAPE)
    {
        _context->setActiveScreen<MainMenuScreen>();
    }
}

GameScreen::~GameScreen() {
}

void GameScreen::update(double deltaTime) {
    _drawSystem.update(deltaTime);
    _audioFacade->playMusic("wildwest");
    _inputFacade->pollEvents();
}
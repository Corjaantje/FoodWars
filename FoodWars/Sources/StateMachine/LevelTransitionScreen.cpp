#include "../../Headers/StateMachine/LevelTransitionScreen.h"
#include "../../Headers/StateMachine/MainMenuScreen.h"
#include "../../Headers/StateMachine/UpgradesScreen.h"

LevelTransitionScreen::LevelTransitionScreen(std::shared_ptr<ScreenStateManager> context) : IScreen(context) {
    visualFacade = context->getFacade<VisualFacade>();
    audioFacade = context->getFacade<AudioFacade>();
    _inputFacade->getKeyEventObservable()->IObservable<KeyEvent>::registerObserver(this);

    _renderList._shapes[1].push_back(createShape<TextButton>(*_inputFacade->getMouseEventObservable(),"Main Menu", [c = _context]() {  c->setActiveScreen<MainMenuScreen>(); }, 250, 30, 200, 200));

    // Upgrades
    _renderList._shapes[1].push_back(createShape<TextButton>(*_inputFacade->getMouseEventObservable(),
            "Upgrades", [c = _context, this]()
            {
                c->setActiveScreen<UpgradesScreen>();
                ((std::static_pointer_cast<UpgradesScreen>( c->getCurrentState())->setPreviousScreen(getScreenName())));
            }, 250, 30, 200, 250));
}

LevelTransitionScreen::~LevelTransitionScreen() = default;

void LevelTransitionScreen::update(double deltaTime) {
    visualFacade->render(_renderList);
    audioFacade->playMusic("menu");
    _inputFacade->pollEvents();
}

void LevelTransitionScreen::update(std::shared_ptr<KeyEvent> event){
    if(event->getKey() == KEY::KEY_ESCAPE)
    {
        _context->setActiveScreen<MainMenuScreen>();
    }
}



#include "../../Headers/StateMachine/LevelTransitionScreen.h"
#include "../../Headers/StateMachine/MainMenuScreen.h"
#include "../../Headers/StateMachine/UpgradesScreen.h"

LevelTransitionScreen::LevelTransitionScreen(std::shared_ptr<ScreenStateManager> context) : IScreen(context) {
    visualFacade = context->getFacade<VisualFacade>();
    audioFacade = context->getFacade<AudioFacade>();
    _inputFacade->getKeyEventObservable()->IObservable<KeyEvent>::registerObserver(this);

    _renderList._shapes[1].push_back(createShape<TextButton>(*_inputFacade->getMouseEventObservable(),"", [c = _context]() {  c->setActiveScreen<MainMenuScreen>(); }, 375, 113, 613, 544));

    // Upgrades
    _renderList._shapes[1].push_back(createShape<TextButton>(*_inputFacade->getMouseEventObservable(),
            "", [c = _context, this]()
            {
                c->setActiveScreen<UpgradesScreen>();
                ((std::static_pointer_cast<UpgradesScreen>( c->getCurrentState())->setPreviousScreen(getScreenName())));
            }, 375, 113, 611, 420));
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

void LevelTransitionScreen::setScore(int score) {
    _renderList._shapes[1].push_back(new ShapeText{790, 75, std::to_string(score), 12, 95, 50, Colour{0,0,0,0}});
}



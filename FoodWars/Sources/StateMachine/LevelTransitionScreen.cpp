#include "../../Headers/StateMachine/LevelTransitionScreen.h"
#include "../../Headers/StateMachine/MainMenuScreen.h"
#include "../../Headers/StateMachine/UpgradesScreen.h"

LevelTransitionScreen::LevelTransitionScreen(ScreenStateManager& context) : IScreen(context) {
    createShape<TextButton>(_inputFacade->getMouseEventObservable(),"",
            [c = _context]() {
                c->setActiveScreen<MainMenuScreen>();
            },
            375, 113, 613, 544)->addToRender(&_renderList);

    createShape<TextButton>(_inputFacade->getMouseEventObservable(),"",
            [c = _context, this]()
            {
                //c->setActiveScreen<UpgradesScreen>();
                //((std::static_pointer_cast<UpgradesScreen>( c->getCurrentState())->setPreviousScreen(getScreenName())));
            },
            375, 113, 611, 420)->addToRender(&_renderList);
}

LevelTransitionScreen::~LevelTransitionScreen() = default;

void LevelTransitionScreen::update(double deltaTime) {
    _visualFacade->render(_renderList);
    _audioFacade->playMusic("menu");
    _inputFacade->pollEvents();
}

void LevelTransitionScreen::update(const KeyEvent& event){
    if(event.getKey() == KEY::KEY_ESCAPE)
    {
        _context->setActiveScreen<MainMenuScreen>();
    }
}

void LevelTransitionScreen::setScore(int score) {
    createShape<ShapeText>(790, 75, std::to_string(score), 12, 95, 50, Colour{0,0,0,0})->addToRender(&_renderList);
}



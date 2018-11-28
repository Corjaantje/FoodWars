#include "../../Headers/StateMachine/PauseScreen.h"
#include "../../../TonicEngine/Headers/Visual/Shapes/TextButton.h"
#include "../../Headers/StateMachine/GameScreen.h"
#include "../../Headers/StateMachine/MainMenuScreen.h"

PauseScreen::PauseScreen(std::shared_ptr<ScreenStateManager> context) : IScreen(context) {
    visualFacade = context->getFacade<VisualFacade>();
    audioFacade = context->getFacade<AudioFacade>();
    _inputFacade->getKeyEventObservable()->registerKeyEventObserver(this);

    auto wallpaper = createShape<ShapeSprite>(1600, 900, 0, 0, "ScreenPause.png");
    wallpaper->layer = 0;
    wallpaper->addToRender(&_renderList);

    // Spel Hervatten
    createShape<TextButton>(*_inputFacade->getMouseEventObservable(),"",
            [c = _context]() {
                c->setActiveScreen<GameScreen>();
            },
            370, 110, 615, 300)->addToRender(&_renderList);

    // Spel Opslaan
    createShape<TextButton>(*_inputFacade->getMouseEventObservable(),"",
            [c = _context]() {
                c->setActiveScreen<GameScreen>();
            },
            370, 110, 615, 420)->addToRender(&_renderList);

    // Terug naar hoofdmenu
    createShape<TextButton>(*_inputFacade->getMouseEventObservable(),"",
            [c = _context]() {
                c->setActiveScreen<MainMenuScreen>();
            },
            370, 110, 615, 540)->addToRender(&_renderList);
}

PauseScreen::~PauseScreen() = default;

void PauseScreen::update(double deltaTime) {
    visualFacade->render(_renderList);
    audioFacade->playMusic("menu");
    _inputFacade->pollEvents();
}

void PauseScreen::update(std::shared_ptr<KeyEvent> event) {
    if(event->getKey() == KEY::KEY_ESCAPE && event->getKeyEventType() == KeyEventType::Down) {
        _context->setActiveScreen<GameScreen>();
    }
}
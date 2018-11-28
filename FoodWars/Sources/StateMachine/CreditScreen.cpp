#include "../../Headers/StateMachine/CreditScreen.h"
#include "../../Headers/StateMachine/MainMenuScreen.h"

CreditScreen::CreditScreen(std::shared_ptr<ScreenStateManager> context) : IScreen(context) {
    visualFacade = context->getFacade<VisualFacade>();
    audioFacade = context->getFacade<AudioFacade>();
    _inputFacade->getKeyEventObservable()->IObservable<KeyEvent>::registerObserver(this);
    _inputFacade->setWindowResolutionCalculator(_context->getWindowResolutionCalculator());

   auto wallpaper = createShape<ShapeSprite>(1600, 900, 0, 0, "ScreenCredits.png");
   wallpaper->layer = 0;
   wallpaper->addToRender(&_renderList);

    createShape<SpriteButton>(*_inputFacade->getMouseEventObservable(), "",
            [c = _context]() {
                c->setActiveScreen<MainMenuScreen>();
            },
            140, 140, 12, 12,
            Colour{0,0,0,0})->addToRender(&_renderList);
}

CreditScreen::~CreditScreen() = default;

void CreditScreen::update(double deltaTime) {
    visualFacade->render(_renderList);
    audioFacade->playMusic("menu");
    _inputFacade->pollEvents();
}

void CreditScreen::update(const KeyEvent& event){
    if(event.getKey() == KEY::KEY_ESCAPE && event.getKeyEventType() == KeyEventType::Down)
    {
        _context->setActiveScreen<MainMenuScreen>();
    }
}
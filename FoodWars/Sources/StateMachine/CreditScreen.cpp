#include "../../Headers/StateMachine/CreditScreen.h"
#include "../../Headers/StateMachine/MainMenuScreen.h"

CreditScreen::CreditScreen(ScreenStateManager& context) : IScreen(context) {
    auto wallpaper = createShape<ShapeSprite>(1600, 900, 0, 0, "ScreenCredits.png");
    wallpaper->layer = 0;
    wallpaper->addToRender(&_renderList);

    createShape<SpriteButton>(_inputFacade->getMouseEventObservable(), "",
            [c = _context]() {
                c->setActiveScreen<MainMenuScreen>();
            },
            140, 140, 12, 12,
            Colour{0,0,0,0})->addToRender(&_renderList);
}

void CreditScreen::update(double deltaTime) {
    _visualFacade->render(_renderList);
    _audioFacade->playMusic("menu");
    _inputFacade->pollEvents();
}

void CreditScreen::update(const KeyEvent& event){
    if(event.getKey() == KEY::KEY_ESCAPE && event.getKeyEventType() == KeyEventType::Down)
    {
        _context->setActiveScreen<MainMenuScreen>();
    }
}
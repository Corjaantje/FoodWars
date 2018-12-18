#include "../../Headers/StateMachine/HelpScreen.h"
#include "../../Headers/StateMachine/MainMenuScreen.h"

HelpScreen::HelpScreen(ScreenStateManager& context) : IScreen(context) {
    _inputFacade->getKeyEventObservable().registerKeyEventObserver(this);
    auto wallpaper = createShape<ShapeSprite>(1600, 900, 0, 0, "ScreenHelp.png");
    wallpaper->layer = 0;
    wallpaper->addToRender(&_renderList);

    createShape<SpriteButton>(_inputFacade->getMouseEventObservable(), "",
            [c = _context]() {
                c->setActiveScreen<MainMenuScreen>();
            },
            140, 140, 12, 12,
            Colour{0,0,0,0})->addToRender(&_renderList);
}

HelpScreen::~HelpScreen() = default;

void HelpScreen::update(double deltaTime) {
    _visualFacade->render(_renderList);
    _audioFacade->playMusic("menu");
    _inputFacade->pollEvents();
}

void HelpScreen::update(const KeyEvent& event){
    if(event.getKey() == KEY::KEY_ESCAPE)
    {
        _context->setActiveScreen<MainMenuScreen>();
    }
}

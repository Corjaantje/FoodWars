#include "../../Headers/StateMachine/HelpScreen.h"
#include "../../Headers/StateMachine/MainMenuScreen.h"

HelpScreen::HelpScreen(ScreenStateManager& context) : IScreen(context) {
    auto wallpaper = createShape<ShapeSprite>(1600, 900, 0, 0, "ScreenHelp.png");
    wallpaper->layer = 0;
    wallpaper->addToRender(&_renderList);

    createShape<SpriteButton>(_inputFacade->getMouseEventObservable(), "",
            [c = _context]() {
                c->setActiveScreen<MainMenuScreen>();
            },
            140, 140, 12, 12,
            Colour{0,0,0,0})->addToRender(&_renderList);

    createShape<ShapeText>(1040, 480, "'A'", 0, 30, 30, Colour(255, 255, 255, 0))->addToRender(&_renderList);
    createShape<ShapeText>(1040, 600, "'D'", 0, 30, 30, Colour(255, 255, 255, 0))->addToRender(&_renderList);
    createShape<ShapeText>(1040, 720, "'Spacebar'", 0, 10 * 20, 30, Colour(255, 255, 255, 0))->addToRender(&_renderList);
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

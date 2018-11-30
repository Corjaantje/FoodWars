#include "../../Headers/StateMachine/UpgradesScreen.h"
#include "../../Headers/StateMachine/MainMenuScreen.h"

UpgradesScreen::UpgradesScreen(ScreenStateManager& context) : IScreen(context) {
    auto wallpaper = createShape<ShapeSprite>(1600, 900, 0, 0, "ScreenUpgrades.png");
    wallpaper->layer = 0;
    wallpaper->addToRender(&_renderList);

    createShape<SpriteButton>(_inputFacade->getMouseEventObservable(), "exit.png",
            [c = _context, &p = _previousScreen]() {
                //c->setActiveScreen(p);
            },
            50, 50, 0, 0,
            Colour{0,0,0,0})->addToRender(&_renderList);
}

UpgradesScreen::~UpgradesScreen() = default;

void UpgradesScreen::update(double deltaTime) {
    _visualFacade->render(_renderList);
    _audioFacade->playMusic("menu");
    _inputFacade->pollEvents();
}

void UpgradesScreen::update(const KeyEvent& event){
    if(event.getKey() == KEY::KEY_ESCAPE)
    {
        _context->setActiveScreen<MainMenuScreen>();
    }
}

void UpgradesScreen::setPreviousScreen(const std::string& screen){
    _previousScreen = screen;
}
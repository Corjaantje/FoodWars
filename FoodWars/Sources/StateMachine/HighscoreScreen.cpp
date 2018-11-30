#include "../../Headers/StateMachine/HighscoreScreen.h"
#include "../../Headers/StateMachine/MainMenuScreen.h"

HighscoreScreen::HighscoreScreen(ScreenStateManager& context) : IScreen(context) {
    auto wallpaper = createShape<ShapeSprite>(1600, 900, 0, 0, "ScreenHighscore.png");
    wallpaper->layer = 0;
    wallpaper->addToRender(&_renderList);

    createShape<SpriteButton>(_inputFacade->getMouseEventObservable(), "",
            [c = _context]() {
                c->setActiveScreen<MainMenuScreen>();
            },
            140, 140, 12, 12,
            Colour{0,0,0,0})->addToRender(&_renderList);

    createShape<ShapeText>(560, 350, "Level 1: ", 0, 200, 85, Colour(255, 255, 255, 0))->addToRender(&_renderList);
    createShape<ShapeText>(560, 510, "Level 2: ", 0, 200, 85, Colour(255, 255, 255, 0))->addToRender(&_renderList);
    createShape<ShapeText>(560, 670, "Level 3: ", 0, 200, 85, Colour(255, 255, 255, 0))->addToRender(&_renderList);
    createShape<ShapeText>(800, 350, _storageFacade->getHighscore(0) + " punten", 0, 250, 85, Colour(255, 255, 255, 0))->addToRender(&_renderList);
    createShape<ShapeText>(800, 510, _storageFacade->getHighscore(1) + " punten", 0, 250, 85, Colour(255, 255, 255, 0))->addToRender(&_renderList);
    createShape<ShapeText>(800, 670, _storageFacade->getHighscore(2) + " punten", 0, 250, 85, Colour(255, 255, 255, 0))->addToRender(&_renderList);
}

HighscoreScreen::~HighscoreScreen() = default;

void HighscoreScreen::update(double deltaTime) {
    _visualFacade->render(_renderList);
    _audioFacade->playMusic("menu");
    _inputFacade->pollEvents();
}

void HighscoreScreen::update(const KeyEvent& event){
    if(event.getKey() == KEY::KEY_ESCAPE && event.getKeyEventType() == KeyEventType::Down)
    {
        _context->setActiveScreen<MainMenuScreen>();
    }
}

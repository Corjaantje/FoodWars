#include "../../Headers/StateMachine/HighscoreScreen.h"

HighscoreScreen::HighscoreScreen(std::shared_ptr<ScreenStateManager> context) : IScreen(context) {
    visualFacade = context->getFacade<VisualFacade>();
    audioFacade = context->getFacade<AudioFacade>();
    _inputFacade->getKeyEventObservable()->registerObserver(this);

    _renderList.spriteList.emplace_back(ShapeSprite{640, 480, 0, 0, "wallpaper.png"});

    _renderList.textList.emplace_back(ShapeText(150, 200, "Level 1: ", 24, 150, 30, Colour(0, 0, 0, 0)));
    _renderList.textList.emplace_back(ShapeText(150, 250, "Level 2: ", 24, 150, 30, Colour(0, 0, 0, 0)));
    _renderList.textList.emplace_back(ShapeText(150, 300, "Level 3: ", 24, 150, 30, Colour(0, 0, 0, 0)));
    _renderList.textList.emplace_back(ShapeText(350, 200, "500 punten", 24, 120, 30, Colour(0, 0, 0, 0)));
    _renderList.textList.emplace_back(ShapeText(350, 250, "200 punten", 24, 120, 30, Colour(0, 0, 0, 0)));
    _renderList.textList.emplace_back(ShapeText(350, 300, "0 punten", 24, 120, 30, Colour(0, 0, 0, 0)));
}

HighscoreScreen::~HighscoreScreen() {
    for(IShape* button: _buttons) {
        delete button;
    }
}

void HighscoreScreen::update(double deltaTime) {
    visualFacade->render(_renderList);
    audioFacade->playMusic("menu");
    _inputFacade->pollEvents();
}

void HighscoreScreen::update(std::shared_ptr<KeyEvent> event){
    if(event->getKey() == KEY::KEY_ESCAPE)
    {
        _isClosed = true;
    }
}

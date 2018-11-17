#include <utility>

#include "../../Headers/StateMachine/LevelSelectionScreen.h"
#include "../../Headers/StateMachine/MainMenuScreen.h"

LevelSelectionScreen::LevelSelectionScreen(std::shared_ptr<ScreenStateManager> context, std::shared_ptr<LevelManager> levelManager) : IScreen(context) {
    audioFacade = context->getFacade<AudioFacade>();
    _inputFacade->getKeyEventObservable()->IObservable<KeyEvent>::registerObserver(this);
    _renderList.spriteList.emplace_back(ShapeSprite{1600, 900, 0, 0, "wallpaperLevelSelect.png"});

    // MainMenu
    SpriteButton* quitButton = new SpriteButton {*_inputFacade->getMouseEventObservable(), "", [c = _context]() {  c->setActiveScreen<MainMenuScreen>(); }, 120, 120, 10, 10, Colour{0,0,0,0}};
    quitButton->addToRender(&_renderList);
    _buttons.push_back(quitButton);

    // Highscore
    //TODO ADD HIGHSCORE SCREEN BUTTON
    SpriteButton* highscorebutton = new SpriteButton {*_inputFacade->getMouseEventObservable(), "", [c = _context]() {  c->setActiveScreen<MainMenuScreen>(); }, 120, 120, 150, 10, Colour{0,0,0,0}};
    highscorebutton->addToRender(&_renderList);
    _buttons.push_back(highscorebutton);

    // Level 1
    TextButton* levelSelectionButton = new TextButton {*_inputFacade->getMouseEventObservable(),"Level 1", [c = _context, levelManager = std::move(levelManager)]() {
        c->addOrSetScreenState(new GameScreen{c, levelManager->startLevel(1)});
        c->setActiveScreen<GameScreen>();
    }, 250, 80, 680, 310, Colour(255, 255, 255, 255), Colour(255, 255, 255, 255)};
    levelSelectionButton->addToRender(&_renderList);
    _buttons.push_back(levelSelectionButton);
}

LevelSelectionScreen::~LevelSelectionScreen() {
    for(IShape* button: _buttons) {
        delete button;
    }
}

void LevelSelectionScreen::update(double deltaTime) {
    visualFacade->render(_renderList);
    audioFacade->playMusic("menu");
    _inputFacade->pollEvents();
}

void LevelSelectionScreen::update(std::shared_ptr<KeyEvent> event){
    if(event->getKey() == KEY::KEY_ESCAPE)
    {
        _context->setActiveScreen<MainMenuScreen>();
    }
}
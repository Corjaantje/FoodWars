#include <utility>

#include "../../Headers/StateMachine/LevelSelectionScreen.h"
#include "../../Headers/StateMachine/MainMenuScreen.h"
#include "../../Headers/StateMachine/LevelTransitionScreen.h"
#include "../../Headers/StateMachine/LoseTransitionScreen.h"
#include "../../Headers/StateMachine/WinTransitionScreen.h"
#include "../../Headers/StateMachine/DrawTransitionScreen.h"

LevelSelectionScreen::LevelSelectionScreen(std::shared_ptr<ScreenStateManager> context, std::shared_ptr<LevelManager> levelManager) : IScreen(context) {
    audioFacade = context->getFacade<AudioFacade>();
    _inputFacade->getKeyEventObservable()->IObservable<KeyEvent>::registerObserver(this);
    _renderList._shapes[0].push_back(new ShapeSprite{1600, 900, 0, 0, "ScreenLevelSelection.png"});

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

    // Win Transition screen
    TextButton* winScreen = new TextButton {*_inputFacade->getMouseEventObservable(),"Win", [c = _context]() {  c->setActiveScreen<WinTransitionScreen>(); }, 250, 30, 200, 250};
    winScreen->addToRender(&_renderList);
    _buttons.push_back(winScreen);

    // Lose Transition screen
    TextButton* loseScreen = new TextButton {*_inputFacade->getMouseEventObservable(),"Lose", [c = _context]() {  c->setActiveScreen<LoseTransitionScreen>(); }, 250, 30, 200, 300};
    loseScreen->addToRender(&_renderList);
    _buttons.push_back(loseScreen);

    // Draw Transition screen
    TextButton* drawScreen = new TextButton {*_inputFacade->getMouseEventObservable(),"Draw", [c = _context]() {  c->setActiveScreen<DrawTransitionScreen>(); }, 250, 30, 200, 350};
    drawScreen->addToRender(&_renderList);
    _buttons.push_back(drawScreen);
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
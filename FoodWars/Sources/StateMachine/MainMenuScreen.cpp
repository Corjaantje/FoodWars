//
// Created by Lucas on 11/10/2018.
//

#include "../../Headers/StateMachine/MainMenuScreen.h"
#include "../../../TonicEngine/Headers/Visual/Shapes/Button.h"
#include "../../Headers/StateMachine/OtherMenuScreen.h"

MainMenuScreen::MainMenuScreen(std::shared_ptr<ScreenStateManager> context) : IScreen(context) {
    visualFacade = context->getFacade<VisualFacade>();
    audioFacade = context->getFacade<AudioFacade>();
    _inputFacade->getKeyEventObservable()->registerObserver(this);

    _renderList.spriteList.emplace_back(ShapeSprite{640, 480, 0, 0, "wallpaper.png"});
    _renderList.rectangleList.emplace_back(ShapeRectangle{440, 40, 100, 100, Colour { 200, 200, 200, 100}});
    //_renderList.textList.emplace_back(ShapeText(200, 200, "Start Game", 180, 250, 45, Colour(0, 0, 0, 0)));

    // Level Selection
    Button* levelSelectionButton = new Button {*_inputFacade->getMouseEventObservable(),"Select Level", [c = _context]() {  c->setActiveScreen<GameScreen>(); }, 250, 30, 200, 200};
    levelSelectionButton->addToRender(&_renderList);
    _buttons.push_back(levelSelectionButton);

    // Level Editor
    Button* levelEditorButton = new Button {*_inputFacade->getMouseEventObservable(),"Level Editor", [c = _context]() {  c->setActiveScreen<GameScreen>(); }, 250, 30, 200, 250};
    levelEditorButton->addToRender(&_renderList);
    _buttons.push_back(levelEditorButton);

    // Upgrades
    Button* upgradesButton = new Button {*_inputFacade->getMouseEventObservable(),"Upgrades", [c = _context]() {  c->setActiveScreen<GameScreen>(); }, 250, 30, 200, 300};
    upgradesButton->addToRender(&_renderList);
    _buttons.push_back(upgradesButton);

    // Settings
    Button* settingsButton = new Button {*_inputFacade->getMouseEventObservable(), [c = _context]() {  c->setActiveScreen<GameScreen>(); }, 50, 50, 530, 0, "settings.png"};
    settingsButton->addToRender(&_renderList);
    _buttons.push_back(settingsButton);

    // Help
    Button* helpButton = new Button {*_inputFacade->getMouseEventObservable(),"Help", [c = _context]() {  c->setActiveScreen<GameScreen>(); }, 100, 30, 0, 390};
    helpButton->addToRender(&_renderList);
    _buttons.push_back(helpButton);

    // Credits
    Button* creditsButton = new Button {*_inputFacade->getMouseEventObservable(),"Credits", [c = _context]() {  c->setActiveScreen<GameScreen>(); }, 100, 30, 0, 430};
    creditsButton->addToRender(&_renderList);
    _buttons.push_back(creditsButton);

    // Quit
    Button* quitButton = new Button {*_inputFacade->getMouseEventObservable(), [c = _context]() {  c->setActiveScreen<GameScreen>(); }, 50, 50, 590, 0, "exit.png"};
    quitButton->addToRender(&_renderList);
    _buttons.push_back(quitButton);

    // High Scores
    Button* highScoresButton = new Button {*_inputFacade->getMouseEventObservable(), [c = _context]() {  c->setActiveScreen<GameScreen>(); }, 50, 50, 0, 0, "trophy.png"};
    highScoresButton->addToRender(&_renderList);
    _buttons.push_back(highScoresButton);



}

MainMenuScreen::~MainMenuScreen() {
    for(Button* button: _buttons) {
        delete button;
    }
}

void MainMenuScreen::update(double deltaTime) {
    visualFacade->render(_renderList);
    audioFacade->playMusic("menu");
    _inputFacade->pollEvents();
}

void MainMenuScreen::update(std::shared_ptr<KeyEvent> event){
    if(event->getKey() == KEY::KEY_ESCAPE)
    {
        _isClosed = true;
    }
}
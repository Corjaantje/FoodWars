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

    Button* startButton = new Button {*_inputFacade->getMouseEventObservable(),"Start Game", [c = _context]() {  c->setActiveScreen<GameScreen>(); }, 250, 60, 200, 200};
    startButton->addToRender(&_renderList);
    _buttons.push_back(startButton);
/*
 *  // this button is for testing purposes only, remove when merging to develop or master
    Button* tempButton  = new Button {*_inputFacade->getMouseEventObservable(), "Second button", [context = _context]() { context->setActiveScreen<OtherMenuScreen>();}, 250, 75, 200, 300};
    tempButton->setXOffSet(50);
    tempButton->setYOffSet(20);
    tempButton->setText("hoi");
    tempButton->setButtonColor(Colour{0, 0, 255, 100});
    tempButton->setButtonPosition(200, 100);
    tempButton->addToRender(&_renderList);
    _buttons.push_back(tempButton);*/
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
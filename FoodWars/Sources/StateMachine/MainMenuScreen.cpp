//
// Created by Lucas on 11/10/2018.
//

#include "../../Headers/StateMachine/MainMenuScreen.h"
#include "../../../TonicEngine/Headers/Visual/Shapes/Button.h"

MainMenuScreen::MainMenuScreen(std::shared_ptr<ScreenStateManager> context) : IScreen(context) {
    visualFacade = context->getFacade<VisualFacade>();
    audioFacade = context->getFacade<AudioFacade>();
    _inputFacade->getMouseEventObservable()->registerObserver(this);
    _inputFacade->getKeyEventObservable()->registerObserver(this);

    _renderList.spriteList.emplace_back(ShapeSprite{640, 480, 0, 0, "../FoodWars/Assets/wallpaper.png"});
    _renderList.rectangleList.emplace_back(ShapeRectangle{440, 40, 100, 100, Colour { 200, 200, 200, 100}});
    //_renderList.textList.emplace_back(ShapeText(200, 200, "Start Game", 180, 250, 45, Colour(0, 0, 0, 0)));

    _startButton = new Button {*_inputFacade->getMouseEventObservable(),"Start Game", [c = _context]() {  c->setActiveScreen<GameScreen>(); }, 250, 60, 200, 200};
    _startButton->addToRender(&_renderList);
}

MainMenuScreen::~MainMenuScreen() {
    delete _startButton;
}

void MainMenuScreen::update(double deltaTime) {
    visualFacade->render(_renderList);
    audioFacade->playMusic("menu");
    _inputFacade->pollEvents();
}

void MainMenuScreen::update(std::shared_ptr<MouseEvent> event){

}

void MainMenuScreen::update(std::shared_ptr<KeyEvent> event){
    if(event->getKey() == KEY::KEY_ESCAPE)
    {
        _isClosed = true;
    }
}
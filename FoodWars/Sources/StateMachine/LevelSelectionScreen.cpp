#include "../../Headers/StateMachine/LevelSelectionScreen.h"
#include "../../Headers/StateMachine/MainMenuScreen.h"

LevelSelectionScreen::LevelSelectionScreen(std::shared_ptr<ScreenStateManager> context) : IScreen(context) {
    visualFacade = context->getFacade<VisualFacade>();
    audioFacade = context->getFacade<AudioFacade>();
    _inputFacade->getKeyEventObservable()->registerObserver(this);

    _renderList.spriteList.emplace_back(ShapeSprite{1600, 900, 0, 0, "wallpaper.png"});

    // MainMenu
    SpriteButton* quitButton = new SpriteButton {*_inputFacade->getMouseEventObservable(), "exit.png", [c = _context]() {  c->setActiveScreen<MainMenuScreen>(); }, 50, 50, 0, 0, Colour{0,0,0,0}};
    quitButton->addToRender(&_renderList);
    _buttons.push_back(quitButton);

    // Level 1
    TextButton* levelSelectionButton = new TextButton {*_inputFacade->getMouseEventObservable(),"Level 1", [c = _context]() {  c->setActiveScreen<GameScreen>(); }, 250, 30, 200, 200};
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
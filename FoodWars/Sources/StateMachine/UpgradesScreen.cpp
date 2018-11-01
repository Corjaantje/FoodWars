#include "../../Headers/StateMachine/UpgradesScreen.h"
#include "../../Headers/StateMachine/MainMenuScreen.h"

UpgradesScreen::UpgradesScreen(std::shared_ptr<ScreenStateManager> context) : IScreen(context) {
    visualFacade = context->getFacade<VisualFacade>();
    audioFacade = context->getFacade<AudioFacade>();
    _inputFacade->getKeyEventObservable()->registerObserver(this);

    _renderList.spriteList.emplace_back(ShapeSprite{640, 480, 0, 0, "wallpaper.png"});

    // MainMenu
    SpriteButton* quitButton = new SpriteButton {*_inputFacade->getMouseEventObservable(), "exit.png", [c = _context]() {  c->setActiveScreen<MainMenuScreen>(); }, 50, 50, 0, 0, Colour{0,0,0,0}};
    quitButton->addToRender(&_renderList);
    _buttons.push_back(quitButton);
}

UpgradesScreen::~UpgradesScreen() {
    for(IShape* button: _buttons) {
        delete button;
    }
}

void UpgradesScreen::update(double deltaTime) {
    visualFacade->render(_renderList);
    audioFacade->playMusic("menu");
    _inputFacade->pollEvents();
}

void UpgradesScreen::update(std::shared_ptr<KeyEvent> event){
    if(event->getKey() == KEY::KEY_ESCAPE)
    {
        _isClosed = true;
    }
}

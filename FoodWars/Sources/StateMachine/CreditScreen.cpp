#include "../../Headers/StateMachine/CreditScreen.h"
#include "../../Headers/StateMachine/MainMenuScreen.h"

CreditScreen::CreditScreen(std::shared_ptr<ScreenStateManager> context) : IScreen(context) {
    visualFacade = context->getFacade<VisualFacade>();
    audioFacade = context->getFacade<AudioFacade>();
    _inputFacade->getKeyEventObservable()->IObservable<KeyEvent>::registerObserver(this);
    _inputFacade->setWindowResolutionCalculator(_context->getWindowResolutionCalculator());

    _renderList._shapes[1].push_back(new ShapeSprite{1600, 900, 0, 0, "ScreenCredits.png"});

    // Backbutton
    SpriteButton* backButton = new SpriteButton {*_inputFacade->getMouseEventObservable(), "", [c = _context]() {  c->setActiveScreen<MainMenuScreen>(); }, 140, 140, 12, 12, Colour{0,0,0,0}};
    backButton->addToRender(&_renderList);
    _buttons.push_back(backButton);
}

CreditScreen::~CreditScreen() {
    for(IShape* button: _buttons) {
        delete button;
    }
}

void CreditScreen::update(double deltaTime) {
    visualFacade->render(_renderList);
    audioFacade->playMusic("menu");
    _inputFacade->pollEvents();
}

void CreditScreen::update(std::shared_ptr<KeyEvent> event){
    if(event->getKey() == KEY::KEY_ESCAPE && event->getKeyEventType() == KeyEventType::Down)
    {
        _context->setActiveScreen<MainMenuScreen>();
    }
}
#include "../../Headers/StateMachine/CreditScreen.h"
#include "../../Headers/StateMachine/MainMenuScreen.h"

CreditScreen::CreditScreen(std::shared_ptr<ScreenStateManager> context) : IScreen(context) {
    visualFacade = context->getFacade<VisualFacade>();
    audioFacade = context->getFacade<AudioFacade>();
    _inputFacade->getKeyEventObservable()->IObservable<KeyEvent>::registerObserver(this);
    _inputFacade->setWindowResolutionCalculator(_context->getWindowResolutionCalculator());

    _renderList.spriteList.emplace_back(ShapeSprite{1600, 900, 0, 0, "wallpaper3.png"});

    // Backbutton
    SpriteButton* backButton = new SpriteButton {*_inputFacade->getMouseEventObservable(), "backbutton.png", [c = _context]() {  c->setActiveScreen<MainMenuScreen>(); }, 100, 100, 9, 9, Colour{0,0,0,0}};
    backButton->addToRender(&_renderList);
    _buttons.push_back(backButton);

    _renderList.textList.emplace_back(ShapeText(610, 130, "Credits", 0, 400, 70, Colour(255,120,112,0)));
    _renderList.textList.emplace_back(ShapeText(660, 320, "Lucas Bos", 0, 300, 45, Colour(255,255,255,0)));
    _renderList.textList.emplace_back(ShapeText(640, 406, "Piet Burgmans", 0, 340, 45, Colour(255,255,255,0)));
    _renderList.textList.emplace_back(ShapeText(645, 492, "Corne Hoskam", 0, 330, 45, Colour(255,255,255,0)));
    _renderList.textList.emplace_back(ShapeText(625, 578, "Bryan van Lierop", 0, 370, 45, Colour(255,255,255,0)));
    _renderList.textList.emplace_back(ShapeText(610, 664, "Maarten van Alebeek", 0, 400, 45, Colour(255,255,255,0)));
    _renderList.textList.emplace_back(ShapeText(620, 750, "Shaun van Beurden", 0, 380, 45, Colour(255,255,255,0)));
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
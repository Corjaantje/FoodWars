#include "../../Headers/StateMachine/CreditScreen.h"
#include "../../Headers/StateMachine/MainMenuScreen.h"

CreditScreen::CreditScreen(std::shared_ptr<ScreenStateManager> context) : IScreen(context) {
    visualFacade = context->getFacade<VisualFacade>();
    audioFacade = context->getFacade<AudioFacade>();
    _inputFacade->getKeyEventObservable()->IObservable<KeyEvent>::registerObserver(this);
    _inputFacade->setWindowResolutionCalculator(_context->getWindowResolutionCalculator());

    _renderList.spriteList.emplace_back(ShapeSprite{1600, 900, 0, 0, "creditscreen.png"});

    // Backbutton
    SpriteButton* backButton = new SpriteButton {*_inputFacade->getMouseEventObservable(), "arrow_back.png", [c = _context]() {  c->setActiveScreen<SettingsScreen>(); }, 50, 50, 10, 10, Colour{0,0,0,0}};
    backButton->addToRender(&_renderList);
    _buttons.push_back(backButton);

    _renderList.textList.emplace_back(ShapeText(720, 150, "Cast", 0, 200, 40, Colour(0, 0, 0, 0)));
    _renderList.textList.emplace_back(ShapeText(660, 250, "Lucas Bos", 0, 300, 35, Colour(0, 0, 0, 0)));
    _renderList.textList.emplace_back(ShapeText(660, 350, "Piet Burgmans", 0, 300, 35, Colour(0, 0, 0, 0)));
    _renderList.textList.emplace_back(ShapeText(660, 450, "Corne Hoskam", 0, 300, 35, Colour(0, 0, 0, 0)));
    _renderList.textList.emplace_back(ShapeText(660, 550, "Bryan van Lierop", 0, 300, 35, Colour(0, 0, 0, 0)));
    _renderList.textList.emplace_back(ShapeText(660, 650, "Maarten van Alebeek", 0, 300, 35, Colour(0, 0, 0, 0)));
    _renderList.textList.emplace_back(ShapeText(660, 750, "Shaun van Beurden", 0, 300, 35, Colour(0, 0, 0, 0)));
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
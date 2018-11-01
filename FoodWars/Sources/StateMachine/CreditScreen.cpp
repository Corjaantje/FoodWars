#include "../../Headers/StateMachine/CreditScreen.h"

CreditScreen::CreditScreen(std::shared_ptr<ScreenStateManager> context) : IScreen(context) {
    visualFacade = context->getFacade<VisualFacade>();
    audioFacade = context->getFacade<AudioFacade>();
    _inputFacade->getKeyEventObservable()->registerObserver(this);

    _renderList.spriteList.emplace_back(ShapeSprite{640, 480, 0, 0, "creditscreen.png"});

    /*Button *backButton = new Button{*_inputFacade->getMouseEventObservable(), "Back to Game",
                                     [c = _context]() { c->setActiveScreen<MainMenuScreen>(); }, 150, 40, 0, 0};
    backButton->addToRender(&_renderList);
    _buttons.push_back(backButton);*/

    _renderList.spriteList.emplace_back(ShapeSprite{40, 40, 10, 10, "arrow_back.png"});

    _renderList.textList.emplace_back(ShapeText(230, 68, "Cast", 180, 200, 40, Colour(0, 0, 0, 0)));
    _renderList.textList.emplace_back(ShapeText(255, 150, "Lucas Bos", 100, 150, 35, Colour(0, 0, 0, 0)));
    _renderList.textList.emplace_back(ShapeText(255, 200, "Piet Burgmans", 100, 150, 35, Colour(0, 0, 0, 0)));
    _renderList.textList.emplace_back(ShapeText(255, 250, "Corne Hoskam", 100, 150, 35, Colour(0, 0, 0, 0)));
    _renderList.textList.emplace_back(ShapeText(255, 300, "Bryan van Lierop", 100, 150, 35, Colour(0, 0, 0, 0)));
    _renderList.textList.emplace_back(ShapeText(255, 350, "Maarten van Alebeek", 100, 150, 35, Colour(0, 0, 0, 0)));
    _renderList.textList.emplace_back(ShapeText(255, 400, "Shaun van Beurden", 100, 150, 35, Colour(0, 0, 0, 0)));
}

CreditScreen::~CreditScreen() {
    for(Button* button: _buttons) {
        delete button;
    }
}

void CreditScreen::update(double deltaTime) {
    visualFacade->render(_renderList);
    audioFacade->playMusic("menu");
    _inputFacade->pollEvents();
}

void CreditScreen::update(std::shared_ptr<KeyEvent> event){
    if(event->getKey() == KEY::KEY_ESCAPE)
    {
        _isClosed = true;
    }
}
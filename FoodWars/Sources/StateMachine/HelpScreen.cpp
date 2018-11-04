#include "../../Headers/StateMachine/HelpScreen.h"

HelpScreen::HelpScreen(std::shared_ptr<ScreenStateManager> context) : IScreen(context) {
    visualFacade = context->getFacade<VisualFacade>();
    audioFacade = context->getFacade<AudioFacade>();
    _inputFacade->getKeyEventObservable()->registerObserver(this);

    _renderList.spriteList.emplace_back(ShapeSprite{640, 480, 0, 0, "howtoplay.png"});

    /*Button *backButton = new Button{*_inputFacade->getMouseEventObservable(), "Back to Game",
                                     [c = _context]() { c->setActiveScreen<MainMenuScreen>(); }, 150, 40, 0, 0};
    backButton->addToRender(&_renderList);
    _buttons.push_back(backButton);*/

    _renderList.spriteList.emplace_back(ShapeSprite{40, 40, 10, 10, "arrow_back.png"});

    _renderList.textList.emplace_back(ShapeText(440, 250, "Controls", 24, 150, 30, Colour(0, 0, 0, 0)));
    _renderList.textList.emplace_back(ShapeText(440, 300, "Move left by pressing A", 24, 150, 22, Colour(0, 0, 0, 0)));
    _renderList.textList.emplace_back(ShapeText(440, 350, "Move right by pressing D", 24, 152, 22, Colour(0, 0, 0, 0)));
    _renderList.textList.emplace_back(ShapeText(440, 400, "Jump by pressing spacebar", 24, 154, 22, Colour(0, 0, 0, 0)));

    /*_renderList.textList.emplace_back(ShapeText(130, 90, "Controls", 180, 400, 40, Colour(0, 0, 0, 0)));
    _renderList.textList.emplace_back(ShapeText(130, 140, "A player can move left by using A", 180, 400, 40, Colour(0, 0, 0, 0)));
    _renderList.textList.emplace_back(ShapeText(130, 190, "A player can move right by using D", 100, 400, 35, Colour(0, 0, 0, 0)));
    _renderList.textList.emplace_back(ShapeText(130, 240, "A player can jump by pressing spacebar", 100, 400, 35, Colour(0, 0, 0, 0)));
    _renderList.textList.emplace_back(ShapeText(80, 290, "How to play", 100, 500, 35, Colour(0, 0, 0, 0)));*/
    //_renderList.spriteList.emplace_back(ShapeSprite(55, 340, 550, 35, "howtoplay.png"));
}

HelpScreen::~HelpScreen() {
    for(Button* button: _buttons) {
        delete button;
    }
}

void HelpScreen::update(double deltaTime) {
    visualFacade->render(_renderList);
    audioFacade->playMusic("menu");
    _inputFacade->pollEvents();
}

void HelpScreen::update(std::shared_ptr<KeyEvent> event){
    if(event->getKey() == KEY::KEY_ESCAPE)
    {
        _isClosed = true;
    }
}

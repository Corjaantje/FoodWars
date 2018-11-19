#include "../../Headers/StateMachine/PauseScreen.h"
#include "../../../TonicEngine/Headers/Visual/Shapes/SpriteButton.h"
#include "../../../TonicEngine/Headers/Visual/Shapes/TextButton.h"
#include "../../Headers/StateMachine/GameScreen.h"
#include "../../Headers/StateMachine/MainMenuScreen.h"

PauseScreen::PauseScreen(std::shared_ptr<ScreenStateManager> context) : IScreen(context) {
    visualFacade = context->getFacade<VisualFacade>();
    audioFacade = context->getFacade<AudioFacade>();
    _inputFacade->getKeyEventObservable()->registerKeyEventObserver(this);

    _renderList._shapes[0].push_back(new ShapeSprite{1600, 900, 0, 0, "ScreenPause.png"});

    // Spel Hervatten
    TextButton* resumeButton = new TextButton {*_inputFacade->getMouseEventObservable(),"", [c = _context]() {  c->setActiveScreen<GameScreen>(); }, 370, 110, 615, 300};
    resumeButton->addToRender(&_renderList);
    _buttons.push_back(resumeButton);

    // Spel Opslaan
    TextButton* saveButton = new TextButton {*_inputFacade->getMouseEventObservable(),"", [c = _context]() {  c->setActiveScreen<GameScreen>(); }, 370, 110, 615, 420};
    saveButton->addToRender(&_renderList);
    _buttons.push_back(saveButton);

    // Terug naar hoofdmenu
    TextButton* quitButton = new TextButton {*_inputFacade->getMouseEventObservable(),"", [c = _context]() {
        c->setActiveScreen<MainMenuScreen>();
    }, 370, 110, 615, 540};
    quitButton->addToRender(&_renderList);
    _buttons.push_back(quitButton);
}

PauseScreen::~PauseScreen() {
    for(IShape* button: _buttons) {
        delete button;
    }
}

void PauseScreen::update(double deltaTime) {
    visualFacade->render(_renderList);
    audioFacade->playMusic("menu");
    _inputFacade->pollEvents();
}

void PauseScreen::update(std::shared_ptr<KeyEvent> event) {
    if(event->getKey() == KEY::KEY_ESCAPE && event->getKeyEventType() == KeyEventType::Down) {
        _context->setActiveScreen<GameScreen>();
    }
}
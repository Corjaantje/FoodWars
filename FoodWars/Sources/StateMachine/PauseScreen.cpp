#include "../../Headers/StateMachine/PauseScreen.h"
#include "../../../TonicEngine/Headers/Visual/Shapes/SpriteButton.h"
#include "../../../TonicEngine/Headers/Visual/Shapes/TextButton.h"
#include "../../Headers/StateMachine/GameScreen.h"
#include "../../Headers/StateMachine/MainMenuScreen.h"

PauseScreen::PauseScreen(std::shared_ptr<ScreenStateManager> context) : IScreen(context) {
    visualFacade = context->getFacade<VisualFacade>();
    audioFacade = context->getFacade<AudioFacade>();

    _renderList.spriteList.emplace_back(ShapeSprite{1600, 900, 0, 0, "wallpaper.png"});

    // Spel Hervatten
    TextButton* resumeButton = new TextButton {*_inputFacade->getMouseEventObservable(),"Spel hervatten", [c = _context]() {  c->setActiveScreen<GameScreen>(); }, 250, 30, 200, 200};
    resumeButton->addToRender(&_renderList);
    _buttons.push_back(resumeButton);

    // Spel Opslaan
    TextButton* saveButton = new TextButton {*_inputFacade->getMouseEventObservable(),"Spel opslaan", [c = _context]() {  c->setActiveScreen<GameScreen>(); }, 250, 30, 200, 250};
    saveButton->addToRender(&_renderList);
    _buttons.push_back(saveButton);

    // Terug naar hoofdmenu
    TextButton* quitButton = new TextButton {*_inputFacade->getMouseEventObservable(),"Terug naar het hoofdmenu", [c = _context]() {
        c->setActiveScreen<MainMenuScreen>();
    }, 250, 30, 200, 300};
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

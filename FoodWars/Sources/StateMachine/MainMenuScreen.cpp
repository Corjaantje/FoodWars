#include "../../Headers/StateMachine/MainMenuScreen.h"
#include "../../Headers/StateMachine/UpgradesScreen.h"


MainMenuScreen::MainMenuScreen(std::shared_ptr<ScreenStateManager> context) : IScreen(context) {
    visualFacade = context->getFacade<VisualFacade>();
    audioFacade = context->getFacade<AudioFacade>();
    _inputFacade->getKeyEventObservable()->registerObserver(this);

    _renderList.spriteList.emplace_back(ShapeSprite{640, 480, 0, 0, "wallpaper.png"});

    // Level Selection
    TextButton* levelSelectionButton = new TextButton {*_inputFacade->getMouseEventObservable(),"Select Level", [c = _context]() {  c->setActiveScreen<LevelSelectionScreen>(); }, 250, 30, 200, 200};
    levelSelectionButton->addToRender(&_renderList);
    _buttons.push_back(levelSelectionButton);

    // Level Editor
    TextButton* levelEditorButton = new TextButton {*_inputFacade->getMouseEventObservable(),"Level Editor", [c = _context]() {  c->setActiveScreen<LevelEditorScreen>(); }, 250, 30, 200, 250};
    levelEditorButton->addToRender(&_renderList);
    _buttons.push_back(levelEditorButton);

    // Upgrades
    TextButton* upgradesButton = new TextButton {*_inputFacade->getMouseEventObservable(),"Upgrades", [c = _context]() {  c->setActiveScreen<UpgradesScreen>(); }, 250, 30, 200, 300};
    upgradesButton->addToRender(&_renderList);
    _buttons.push_back(upgradesButton);

    // Settings
    SpriteButton* settingsButton = new SpriteButton {*_inputFacade->getMouseEventObservable(), "settings.png", [c = _context]() {  c->setActiveScreen<SettingsScreen>(); }, 50, 50, 530, 0, Colour{0,0,0,0}};
    settingsButton->addToRender(&_renderList);
    _buttons.push_back(settingsButton);

    // Help
    TextButton* helpButton = new TextButton {*_inputFacade->getMouseEventObservable(),"Help", [c = _context]() {  c->setActiveScreen<GameScreen>(); }, 100, 30, 0, 390};
    helpButton->addToRender(&_renderList);
    _buttons.push_back(helpButton);

    // Credits
    TextButton* creditsButton = new TextButton {*_inputFacade->getMouseEventObservable(),"Credits", [c = _context]() {  c->setActiveScreen<GameScreen>(); }, 100, 30, 0, 430};
    creditsButton->addToRender(&_renderList);
    _buttons.push_back(creditsButton);

    // Quit
    SpriteButton* quitButton = new SpriteButton {*_inputFacade->getMouseEventObservable(), "exit.png", [this]() { this->quitGame(); }, 50, 50, 590, 0, Colour{0,0,0,0}};
    quitButton->addToRender(&_renderList);
    _buttons.push_back(quitButton);

    // High Scores
    SpriteButton* highScoresButton = new SpriteButton {*_inputFacade->getMouseEventObservable(), "trophy.png", [c = _context]() {  c->setActiveScreen<GameScreen>(); }, 50, 50, 0, 0, Colour{0,0,0,0}};
    highScoresButton->addToRender(&_renderList);
    _buttons.push_back(highScoresButton);
}

MainMenuScreen::~MainMenuScreen() {
    for(IShape* button: _buttons) {
        delete button;
    }
}

void MainMenuScreen::update(double deltaTime) {
    visualFacade->render(_renderList);
    audioFacade->playMusic("menu");
    _inputFacade->pollEvents();
}

void MainMenuScreen::update(std::shared_ptr<KeyEvent> event){
    if(event->getKey() == KEY::KEY_ESCAPE)
    {
        _isClosed = true;
    }
}

void MainMenuScreen::quitGame(){
    _isClosed = true;
}
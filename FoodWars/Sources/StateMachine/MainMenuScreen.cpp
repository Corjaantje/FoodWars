#include "../../Headers/StateMachine/MainMenuScreen.h"
#include "../../Headers/StateMachine/UpgradesScreen.h"


MainMenuScreen::MainMenuScreen(std::shared_ptr<ScreenStateManager> context) : IScreen(context) {
    audioFacade = context->getFacade<AudioFacade>();
    _inputFacade->getKeyEventObservable()->IObservable<KeyEvent>::registerObserver(this);
    _renderList.spriteList.emplace_back(ShapeSprite{1600, 900, 0, 0, "wallpaper2.png"});

    // Level Selection
    TextButton* levelSelectionButton = new TextButton {*_inputFacade->getMouseEventObservable(),"Select Level", [c = _context]() {  c->setActiveScreen<LevelSelectionScreen>(); }, 370, 110, 615, 300, Colour{255,255,255,0}, Colour{255,255,255,0}};
    levelSelectionButton->addToRender(&_renderList);
    _buttons.push_back(levelSelectionButton);

    // Level Editor
    TextButton* levelEditorButton = new TextButton {*_inputFacade->getMouseEventObservable(),"Level Editor", [c = _context]() {  c->setActiveScreen<LevelEditorScreen>(); }, 370, 110, 615, 420, Colour{255,255,255,0}, Colour{255,255,255,0}};
    levelEditorButton->addToRender(&_renderList);
    _buttons.push_back(levelEditorButton);

    // Upgrades
    TextButton* upgradesButton = new TextButton {*_inputFacade->getMouseEventObservable(),"Upgrades", [c = _context]() {  c->setActiveScreen<UpgradesScreen>(); }, 370, 110, 615, 540, Colour{255,255,255,0}, Colour{255,255,255,0}};
    upgradesButton->addToRender(&_renderList);
    _buttons.push_back(upgradesButton);

    // Settings
    SpriteButton* settingsButton = new SpriteButton {*_inputFacade->getMouseEventObservable(), "settings.png", [c = _context]() {  c->setActiveScreen<SettingsScreen>(); }, 120, 120, 1335, 10, Colour{0,0,0,0}};
    settingsButton->addToRender(&_renderList);
    _buttons.push_back(settingsButton);

    // Help
    TextButton* helpButton = new TextButton {*_inputFacade->getMouseEventObservable(),"Help", [c = _context]() {  c->setActiveScreen<GameScreen>(); }, 190, 100, 10, 680, Colour{255,255,255,0}, Colour{255,255,255,0}};
    helpButton->addToRender(&_renderList);
    _buttons.push_back(helpButton);

    // Credits
    TextButton* creditsButton = new TextButton {*_inputFacade->getMouseEventObservable(),"Credits", [c = _context]() {  std::cout << "Credits clicked." << std::endl; c->setActiveScreen<GameScreen>(); }, 190, 100, 10, 790, Colour{255,255,255,0}, Colour{255,255,255,0}};
    creditsButton->addToRender(&_renderList);
    _buttons.push_back(creditsButton);

    // Quit
    SpriteButton* quitButton = new SpriteButton {*_inputFacade->getMouseEventObservable(), "exit.png", [this]() { this->quitGame(); }, 120, 120, 1476, 10, Colour{0,0,0,0}};
    quitButton->addToRender(&_renderList);
    _buttons.push_back(quitButton);

    // High Scores
    SpriteButton* highScoresButton = new SpriteButton {*_inputFacade->getMouseEventObservable(), "trophy.png", [c = _context]() {  c->setActiveScreen<GameScreen>(); }, 120, 120, 10, 10, Colour{0,0,0,0}};
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
    if(event->getKey() == KEY::KEY_ESCAPE && event->getKeyEventType() == KeyEventType::Down)
    {
        _context->setActiveScreen<MainMenuScreen>();
    }
}

void MainMenuScreen::quitGame(){
    _isClosed = true;
}
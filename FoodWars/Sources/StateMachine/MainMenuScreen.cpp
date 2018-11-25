#include "../../Headers/StateMachine/MainMenuScreen.h"
#include "../../Headers/StateMachine/UpgradesScreen.h"
#include "../../Headers/StateMachine/HelpScreen.h"
#include "../../Headers/StateMachine/CreditScreen.h"
#include "../../Headers/StateMachine/HighscoreScreen.h"
#include "../../Headers/StateMachine/AdvertisingScreen.h"


MainMenuScreen::MainMenuScreen(std::shared_ptr<ScreenStateManager> context, const FileManager& fileManager) :
    IScreen(context),
    _fileManager(&fileManager) {

    audioFacade = context->getFacade<AudioFacade>();
    _inputFacade->getKeyEventObservable()->IObservable<KeyEvent>::registerObserver(this);

    _inputFacade->setWindowResolutionCalculator(_context->getWindowResolutionCalculator());
    _renderList._shapes[1].push_back(createShape<ShapeSprite>(1600, 900, 0, 0, "ScreenMainMenu.png"));
    
    // Level Selection
    TextButton *levelSelectionButton = new TextButton{*_inputFacade->getMouseEventObservable(), "Select Level",
                                                      [c = _context]() {
                                                          c->setActiveScreen<LevelSelectionScreen>();
                                                          (std::static_pointer_cast<LevelSelectionScreen>(
                                                                  c->getCurrentState())->generateLevelButtons());
                                                      }, 370, 110, 615, 300, Colour{255, 255, 255, 0},
                                                      Colour{255, 255, 255, 0},};
    levelSelectionButton->addToRender(&_renderList);
    _sprites.push_back(levelSelectionButton);

    // Level Editor
    TextButton* levelEditorButton = new TextButton {*_inputFacade->getMouseEventObservable(),"Level Editor", [c = _context]() {  c->setActiveScreen<LevelCreationScreen>(); }, 370, 110, 615, 420, Colour{255,255,255,0}, Colour{255,255,255,0}};
    levelEditorButton->addToRender(&_renderList);
    _sprites.push_back(levelEditorButton);

    // Upgrades
    TextButton* upgradesButton = new TextButton {*_inputFacade->getMouseEventObservable(),"Upgrades", [c = _context]() {  c->setActiveScreen<UpgradesScreen>(); }, 370, 110, 615, 540, Colour{255,255,255,0}, Colour{255,255,255,0}};
    upgradesButton->addToRender(&_renderList);
    _sprites.push_back(upgradesButton);

    // Settings
    SpriteButton* settingsButton = new SpriteButton {*_inputFacade->getMouseEventObservable(), "", [c = _context]() {  c->setActiveScreen<SettingsScreen>(); }, 120, 120, 1335, 10, Colour{0,0,0,0}};
    settingsButton->addToRender(&_renderList);
    _sprites.push_back(settingsButton);

    // Help
    TextButton* helpButton = new TextButton {*_inputFacade->getMouseEventObservable(),"Help", [c = _context]() {  c->setActiveScreen<HelpScreen>(); }, 190, 100, 10, 680, Colour{255,255,255,0}, Colour{255,255,255,0}};
    helpButton->addToRender(&_renderList);
    _sprites.push_back(helpButton);

    // Credits
    TextButton* creditsButton = new TextButton {*_inputFacade->getMouseEventObservable(),"Credits", [c = _context]() {  c->setActiveScreen<CreditScreen>(); }, 190, 100, 10, 790, Colour{255,255,255,0}, Colour{255,255,255,0}};
    creditsButton->addToRender(&_renderList);
    _sprites.push_back(creditsButton);

    // Advertisement
    _advertisement = new SpriteButton {*_inputFacade->getMouseEventObservable(), _fileManager->readFileContent("./Assets/Sprites/Advertisements/current.txt"), [c = _context]() {  c->setActiveScreen<AdvertisingScreen>(); }, 400, 150, 300, 750, Colour{255,255,255,0}};
    _advertisement->addToRender(&_renderList);
    _sprites.push_back(_advertisement);

    // Quit
    SpriteButton* quitButton = new SpriteButton {*_inputFacade->getMouseEventObservable(), "", [this]() { this->quitGame(); }, 120, 120, 1476, 10, Colour{0,0,0,0}};
    quitButton->addToRender(&_renderList);
    _sprites.push_back(quitButton);

    // High Scores
    SpriteButton* highScoresButton = new SpriteButton {*_inputFacade->getMouseEventObservable(), "", [c = _context]() {  c->setActiveScreen<HighscoreScreen>(); }, 120, 120, 10, 10, Colour{0,0,0,0}};
    highScoresButton->addToRender(&_renderList);
    _sprites.push_back(highScoresButton);
}

MainMenuScreen::~MainMenuScreen() {
    for (IShape *button: _sprites) {
        delete button;
    }
}

void MainMenuScreen::update(double deltaTime) {
    visualFacade->render(_renderList);
    audioFacade->playMusic("menu");
    _inputFacade->pollEvents();
    _advertisement->changeImageURL(_fileManager->readFileContent("./Assets/Sprites/Advertisements/current.txt"));
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
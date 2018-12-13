#include "../../Headers/StateMachine/MainMenuScreen.h"
#include "../../Headers/StateMachine/UpgradesScreen.h"
#include "../../Headers/StateMachine/HelpScreen.h"
#include "../../Headers/StateMachine/CreditScreen.h"
#include "../../Headers/StateMachine/HighscoreScreen.h"
#include "../../Headers/StateMachine/AdvertisingScreen.h"


MainMenuScreen::MainMenuScreen(ScreenStateManager& context) :
    IScreen(context),
    _fileManager(FileManager{}) {

    createShape<ShapeSprite>(1600, 900, 0, 0, "ScreenMainMenu.png")->addToRender(&_renderList);
    
    // Level Selection
    createShape<TextButton>(_inputFacade->getMouseEventObservable(), "Select Level",
            [c = _context]() {
                c->setActiveScreen(std::make_unique<LevelSelectionScreen>(*c));
            },
            370, 110, 615, 300,
            Colour{255, 255, 255, 0},
            Colour{255, 255, 255, 0})->addToRender(&_renderList);

    // Level Editor
    createShape<TextButton>(_inputFacade->getMouseEventObservable(),"Level Editor",
            [c = _context]() {
                c->setActiveScreen(std::make_unique<LevelCreationScreen>(*c));
                //c->createOrSetActiveScreen<LevelCreationScreen>();
            },
            370, 110, 615, 420,
            Colour{255,255,255,0},
            Colour{255,255,255,0})->addToRender(&_renderList);

    // Settings
    createShape<SpriteButton>(_inputFacade->getMouseEventObservable(), "",
            [c = _context]() {
                c->createOrSetActiveScreen<SettingsScreen>();
            },
            120, 120, 1335, 10,
            Colour{0,0,0,0})->addToRender(&_renderList);

    // Help
    createShape<TextButton>(_inputFacade->getMouseEventObservable(),"Help",
            [c = _context]() {
                c->createOrSetActiveScreen<HelpScreen>();
            },
            190, 100, 10, 680,
            Colour{255,255,255,0},
            Colour{255,255,255,0})->addToRender(&_renderList);

    // Credits
    createShape<TextButton>(_inputFacade->getMouseEventObservable(),"Credits",
            [c = _context]() {
                c->createOrSetActiveScreen<CreditScreen>();
            },
            190, 100, 10, 790,
            Colour{255,255,255,0},
            Colour{255,255,255,0})->addToRender(&_renderList);

    // Advertisement
    _advertisement = createShape<SpriteButton>(_inputFacade->getMouseEventObservable(), _fileManager.readFileLines("./Assets/Sprites/Advertisements/current.txt")[0],
            [c = _context]() {
                c->createOrSetActiveScreen<AdvertisingScreen>();
            },
            400, 150, 300, 750,
            Colour{255,255,255,0});
    _advertisement->addToRender(&_renderList);

    // Quit
    createShape<SpriteButton>(_inputFacade->getMouseEventObservable(), "",
            [this]() {
                this->quitGame();
            },
            120, 120, 1476, 10,
            Colour{0,0,0,0})->addToRender(&_renderList);

    // High Scores
    createShape<SpriteButton>(_inputFacade->getMouseEventObservable(), "",
            [c = _context]() {
                c->createOrSetActiveScreen<HighscoreScreen>();
            },
            120, 120, 10, 10,
            Colour{0,0,0,0})->addToRender(&_renderList);
}

MainMenuScreen::~MainMenuScreen() = default;

void MainMenuScreen::update(double deltaTime) {
    _visualFacade->render(_renderList);
    _audioFacade->playMusic("menu");
    _inputFacade->pollEvents();
    _advertisement->changeImageURL(_fileManager.readFileLines("./Assets/Sprites/Advertisements/current.txt")[0]);
}

void MainMenuScreen::update(const KeyEvent& event){
    if(event.getKey() == KEY::KEY_ESCAPE && event.getKeyEventType() == KeyEventType::Down)
    {
        _context->setActiveScreen<MainMenuScreen>();
    }
}

void MainMenuScreen::quitGame(){
    _isClosed = true;
}


#include "../../Headers/StateMachine/LevelCreationScreen.h"
#include "../../Headers/StateMachine/MainMenuScreen.h"

LevelCreationScreen::LevelCreationScreen(std::shared_ptr<ScreenStateManager> context) : IScreen(context) {
    visualFacade = context->getFacade<VisualFacade>();
    audioFacade = context->getFacade<AudioFacade>();
    _inputFacade->getKeyEventObservable()->IObservable<KeyEvent>::registerObserver(this);
    _inputFacade->getMouseEventObservable()->registerObserver(this);
    _windowResCalc = _context->getWindowResolutionCalculator();
    _inputFacade->setWindowResolutionCalculator(_context->getWindowResolutionCalculator());

    _levelBuilder.addWallpaperConfig("WallpaperCity.png");
    _levelBuilder.addWallpaperConfig("WallpaperSky.png");
    _levelBuilder.addWallpaperConfig("WallpaperNature.png");
    _levelBuilder.addMusicConfig("wildwest");

    selectedSong = "none";
    this->initButtons();
}

void LevelCreationScreen::initButtons() {

    //save attempt non const lvalue reference cannot bind to a temporary of type
    SpriteButton* saveButton = new SpriteButton {*_inputFacade->getMouseEventObservable(), "settings.png", [this] { relinkAndSave(); }, 50, 50, 0, 100, Colour{0,0,0,0}};
    saveButton->addToRender(&_renderList);
    _sprites.push_back(saveButton);


    // MainMenu
    SpriteButton* quitButton = new SpriteButton {*_inputFacade->getMouseEventObservable(), "", [c = _context]() {  c->setActiveScreen<MainMenuScreen>(); }, 50, 50, 0, 0, Colour{0,0,0,0}};
    quitButton->addToRender(&_renderList);
    _sprites.push_back(quitButton);

    //Color Red Increment
    SpriteButton* RedIncrementButton = new SpriteButton {*_inputFacade->getMouseEventObservable(), "", [this] { _levelBuilder.incrementColorRed(); }, 50, 50, 1520, 10, Colour{0,0,0,0}};
    RedIncrementButton->addToRender(&_renderList);
    _sprites.push_back(RedIncrementButton);

    //Color Red Decrement
    SpriteButton* RedDecrementButton = new SpriteButton {*_inputFacade->getMouseEventObservable(), "", [this] { _levelBuilder.decrementColorRed(); }, 50, 50, 1370, 10, Colour{0,0,0,0}};
    RedDecrementButton->addToRender(&_renderList);
    _sprites.push_back(RedDecrementButton);

    //Color Green Increment
    SpriteButton* GreenIncrementButton = new SpriteButton {*_inputFacade->getMouseEventObservable(), "", [this] { _levelBuilder.incrementColorGreen(); }, 50, 50, 1520, 75, Colour{0,0,0,0}};
    GreenIncrementButton->addToRender(&_renderList);
    _sprites.push_back(GreenIncrementButton);

    //Color Green Decrement
    SpriteButton* GreenDecrementButton = new SpriteButton {*_inputFacade->getMouseEventObservable(), "", [this] { _levelBuilder.decrementColorGreen(); }, 50, 50, 1370, 75, Colour{0,0,0,0}};
    GreenDecrementButton->addToRender(&_renderList);
    _sprites.push_back(GreenDecrementButton);

    //Color Blue Increment
    SpriteButton* BlueIncrementButton = new SpriteButton {*_inputFacade->getMouseEventObservable(), "", [this] { _levelBuilder.incrementColorBlue(); }, 50, 50, 1520, 140, Colour{0,0,0,0}};
    BlueIncrementButton->addToRender(&_renderList);
    _sprites.push_back(BlueIncrementButton);

    //Color Blue Decrement
    SpriteButton* BlueDecrementButton = new SpriteButton {*_inputFacade->getMouseEventObservable(), "", [this] { _levelBuilder.decrementColorBlue(); }, 50, 50, 1370, 140, Colour{0,0,0,0}};
    BlueDecrementButton->addToRender(&_renderList);
    _sprites.push_back(BlueDecrementButton);


    //Wallpaper Next
    SpriteButton* WallpaperNext = new SpriteButton {*_inputFacade->getMouseEventObservable(), "", [this] { _levelBuilder.setNextWallpaper(); }, 50, 50, 710, 10, Colour{0,0,0,0}};
    WallpaperNext->addToRender(&_renderList);
    _sprites.push_back(WallpaperNext);

    //Wallpaper Previous
    SpriteButton* WallpaperPrevious = new SpriteButton {*_inputFacade->getMouseEventObservable(), "", [this] { _levelBuilder.setPreviousWallpaper(); }, 50, 50, 460, 10, Colour{0,0,0,0}};
    WallpaperPrevious->addToRender(&_renderList);
    _sprites.push_back(WallpaperPrevious);

    //Music Next
    SpriteButton* MusicNext = new SpriteButton {*_inputFacade->getMouseEventObservable(), "", [this] {
        _levelBuilder.setNextMusic();
        selectedSong = _levelBuilder.getSelectedSong();
        }, 50, 50, 710, 80, Colour{0,0,0,0}};
    MusicNext->addToRender(&_renderList);
    _sprites.push_back(MusicNext);

    //Music Previous
    SpriteButton* MusicPrevious = new SpriteButton {*_inputFacade->getMouseEventObservable(), "", [this] {
        _levelBuilder.setPreviousMusic();
        selectedSong = _levelBuilder.getSelectedSong();
        }, 50, 50, 460, 80, Colour{0,0,0,0}};
    MusicPrevious->addToRender(&_renderList);
    _sprites.push_back(MusicPrevious);

    toggleCollidable = new SpriteButton {*_inputFacade->getMouseEventObservable(), "stateOff.png", [this] {
        bool state = _levelBuilder.toggleCollidable();
        if (state) {
            toggleCollidable->changeImageURL(std::string("stateOn.png"));
        } else {
            toggleCollidable->changeImageURL(std::string("stateOff.png"));
        }
    }, 50, 50, 1030, 10, Colour{0, 0, 0, 0}};
    _sprites.push_back(toggleCollidable);

    toggleDamageable = new SpriteButton {*_inputFacade->getMouseEventObservable(), "stateOff.png", [this] {
        bool state = _levelBuilder.toggleDamageable();
        if (state) {
            toggleDamageable->changeImageURL(std::string("stateOn.png"));
        } else {
            toggleDamageable->changeImageURL(std::string("stateOff.png"));
        }
    }, 50, 50, 1030, 85, Colour{0, 0, 0, 0}};
    _sprites.push_back(toggleDamageable);

    toggleBuildTerrain = new SpriteButton {*_inputFacade->getMouseEventObservable(), "stateOn.png", [this] {
        buildTerrainActive = !buildTerrainActive;
        if (buildTerrainActive) {
            toggleBuildTerrain->changeImageURL(std::string("stateOn.png"));
            toggleSetSpawn->changeImageURL(std::string("stateOff.png"));
        } else {
            toggleBuildTerrain->changeImageURL(std::string("stateOff.png"));
            toggleSetSpawn->changeImageURL(std::string("stateOn.png"));
        }
    }, 50, 50, 355, 10, Colour{0, 0, 0, 0}};
    _sprites.push_back(toggleBuildTerrain);

    toggleSetSpawn = new SpriteButton {*_inputFacade->getMouseEventObservable(), "stateOff.png", [this] {
        buildTerrainActive = !buildTerrainActive;
        if (!buildTerrainActive) {
            toggleSetSpawn->changeImageURL(std::string("stateOn.png"));
            toggleBuildTerrain->changeImageURL(std::string("stateOff.png"));
        } else {
            toggleSetSpawn->changeImageURL(std::string("stateOff.png"));
            toggleBuildTerrain->changeImageURL(std::string("stateOn.png"));
        }
    }, 50, 50, 355, 75, Colour{0, 0, 0, 0}};
    _sprites.push_back(toggleSetSpawn);
}

LevelCreationScreen::~LevelCreationScreen() = default;

void LevelCreationScreen::update(double deltaTime) {
    audioFacade->playMusic("menu");
    _inputFacade->pollEvents();
}

void LevelCreationScreen::update(std::shared_ptr<KeyEvent> event){
    if(event->getKey() == KEY::KEY_ESCAPE)
    {
        _context->setActiveScreen<MainMenuScreen>();
        this->callRender();
    }
}

void LevelCreationScreen::update(std::shared_ptr<MouseEvent> event) {
    this->callRender();
    if(this->buildTerrainActive) {
        if (event->getMouseEventType() == MouseEventType::Down && event->getMouseClickType() == MouseClickType::Left) {
            _levelBuilder.placeBlock(event->getXPosition(), event->getYPosition());
        }
        if (event->getMouseEventType() == MouseEventType::Down && event->getMouseClickType() == MouseClickType::Right) {
            _levelBuilder.removeBlock(event->getXPosition(), event->getYPosition());
        }
    }
    else{
        if (event->getMouseEventType() == MouseEventType::Down && event->getMouseClickType() == MouseClickType::Left) {
            _levelBuilder.placeSpawnPoint(event->getXPosition(), event->getYPosition());
        }
        if (event->getMouseEventType() == MouseEventType::Down && event->getMouseClickType() == MouseClickType::Right) {
            _levelBuilder.removeSpawnPoint(event->getXPosition(), event->getYPosition());
        }
    }
}

void LevelCreationScreen::callRender() {
    _renderList.clearLists();
    _levelBuilder.drawCurrentScene(_renderList);
    for (int i = 0; i < _sprites.size(); i++) {
        _sprites[i]->addToRender(&_renderList);
    }
    _renderList._shapes[1].push_back(new ShapeText(610 - selectedSong.size() * 10, 130, selectedSong, 150, selectedSong.size() * 20, 50, Colour(0, 0, 0, 0)));
    visualFacade->render(_renderList);
}

void LevelCreationScreen::relinkAndSave() {
    StorageSystem storage;
    EntityManager ent = _levelBuilder.buildConstructedLevel().getEntityManager();
    // spawnpoints
    std::vector<Coordinate> spawns = _levelBuilder.getSpawnPoints();
    // background image?

    // background music

    storage.assignRelevantEntityManager(ent);
    storage.saveWorld();
}

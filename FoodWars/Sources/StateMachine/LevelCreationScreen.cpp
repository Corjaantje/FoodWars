#include "../../Headers/StateMachine/LevelCreationScreen.h"
#include "../../Headers/StateMachine/MainMenuScreen.h"
#include "../../Headers/Storage/LevelStorage.h"

LevelCreationScreen::LevelCreationScreen(ScreenStateManager& context) : IScreen(context), selectedSong{"none"}, countTime(false), _deltaTime(0.0)
{
    _inputFacade->getKeyEventObservable().IObservable<KeyEvent>::registerObserver(this);
    _inputFacade->getMouseEventObservable().registerObserver(this);
    this->initButtons();
    selectedSongText = createShape<ShapeText>(610 - selectedSong.size() * 10, 130, selectedSong, 150, selectedSong.size() * 20, 50, Colour(0, 0, 0, 0));
}

void LevelCreationScreen::initButtons() {

    //save attempt non const lvalue reference cannot bind to a temporary of type
    createShape<SpriteButton>(_inputFacade->getMouseEventObservable(), "",
            [this] () {
                if(_levelBuilder.canBuildLevel()){
                        auto it = std::find(_sprites.begin(), _sprites.end(), savingLevel);
                        if (it != _sprites.end()) {
                            using std::swap;
                            swap(*it, _sprites.back());
                            _sprites.pop_back();
                        }
                        savingLevel = createShape<ShapeText>(10, 130, "Saving Level...", 0, 340, 45, Colour(255, 255, 255, 0));
                        savingLevel->addToRender(&_renderList);
                        //Force an update to render the loading level.
                        this->update(0);
                        countTime = true;
                        relinkAndSave();
                }
            },
            50, 50, 0, 75,
            Colour{0,0,0,0});

    createShape<SpriteButton>(_inputFacade->getMouseEventObservable(), "",
            [c = _context]() {
                c->setActiveScreen<MainMenuScreen>();
            },
            50, 50, 0, 0,
            Colour{0,0,0,0});

    //Color Red Increment
    createShape<SpriteButton>(_inputFacade->getMouseEventObservable(), "",
            [this]() {
                _levelBuilder.incrementColorRed();
            },
            50, 50, 1520, 10,
            Colour{0,0,0,0});

    //Color Red Decrement
    createShape<SpriteButton>(_inputFacade->getMouseEventObservable(), "",
            [this]() {
                _levelBuilder.decrementColorRed();
            },
            50, 50, 1370, 10,
            Colour{0,0,0,0});

    //Color Green Increment
    createShape<SpriteButton>(_inputFacade->getMouseEventObservable(), "",
            [this]() {
                _levelBuilder.incrementColorGreen();
            },
            50, 50, 1520, 75,
            Colour{0,0,0,0});

    //Color Green Decrement
    createShape<SpriteButton>(_inputFacade->getMouseEventObservable(), "",
            [this]() {
                _levelBuilder.decrementColorGreen();
            },
            50, 50, 1370, 75,
            Colour{0,0,0,0});

    //Color Blue Increment
    createShape<SpriteButton>(_inputFacade->getMouseEventObservable(), "",
            [this]() {
                _levelBuilder.incrementColorBlue();
            },
            50, 50, 1520, 140,
            Colour{0,0,0,0});

    //Color Blue Decrement
    createShape<SpriteButton>(_inputFacade->getMouseEventObservable(), "",
            [this]() {
                _levelBuilder.decrementColorBlue();
            },
            50, 50, 1370, 140,
            Colour{0,0,0,0});

    //Wallpaper Next
    createShape<SpriteButton>(_inputFacade->getMouseEventObservable(), "",
            [this]() {
                _levelBuilder.setNextWallpaper();
            },
            50, 50, 710, 10,
            Colour{0,0,0,0});

    //Wallpaper Previous
    createShape<SpriteButton>(_inputFacade->getMouseEventObservable(), "",
            [this]() {
                _levelBuilder.setPreviousWallpaper();
            },
            50, 50, 460, 10,
            Colour{0,0,0,0});

    //Music Next
    createShape<SpriteButton>(_inputFacade->getMouseEventObservable(), "",
            [this]() {
                _levelBuilder.setNextMusic();
                selectedSong = _levelBuilder.getSelectedSong();
            },
            50, 50, 710, 80,
            Colour{0,0,0,0});

    //Music Previous
    createShape<SpriteButton>(_inputFacade->getMouseEventObservable(), "",
            [this]() {
                _levelBuilder.setPreviousMusic();
                selectedSong = _levelBuilder.getSelectedSong();
            },
            50, 50, 460, 80,
            Colour{0,0,0,0});

    //toggleCollidable
    toggleCollidable = createShape<SpriteButton>(_inputFacade->getMouseEventObservable(), "stateOn.png",
            [this]() {
                bool state = _levelBuilder.toggleCollidable();
                if (state) {
                    toggleCollidable->changeImageURL(std::string("stateOn.png"));
                } else {
                    toggleCollidable->changeImageURL(std::string("stateOff.png"));
                }
            },
            50, 50, 1030, 10,
            Colour{0, 0, 0, 0});

    //toggleDamageable
    toggleDamageable = createShape<SpriteButton>(_inputFacade->getMouseEventObservable(), "stateOn.png",
            [this]() {
                bool state = _levelBuilder.toggleDamageable();
                if (state) {
                    toggleDamageable->changeImageURL(std::string("stateOn.png"));
                } else {
                    toggleDamageable->changeImageURL(std::string("stateOff.png"));
                }
            },
            50, 50, 1030, 85,
            Colour{0, 0, 0, 0});

    //toggleBuildTerrain
    toggleBuildTerrain = createShape<SpriteButton>(_inputFacade->getMouseEventObservable(), "stateOn.png",
            [this]() {
                buildTerrainActive = !buildTerrainActive;
                if (buildTerrainActive) {
                    toggleBuildTerrain->changeImageURL(std::string("stateOn.png"));
                    toggleSetSpawn->changeImageURL(std::string("stateOff.png"));
                } else {
                    toggleBuildTerrain->changeImageURL(std::string("stateOff.png"));
                    toggleSetSpawn->changeImageURL(std::string("stateOn.png"));
                }
            },
            50, 50, 355, 10,
            Colour{0, 0, 0, 0});

    //toggleSetSpawn
    toggleSetSpawn = createShape<SpriteButton>(_inputFacade->getMouseEventObservable(), "stateOff.png",
            [this]() {
                buildTerrainActive = !buildTerrainActive;
                if (!buildTerrainActive) {
                    toggleSetSpawn->changeImageURL(std::string("stateOn.png"));
                    toggleBuildTerrain->changeImageURL(std::string("stateOff.png"));
                } else {
                    toggleSetSpawn->changeImageURL(std::string("stateOff.png"));
                    toggleBuildTerrain->changeImageURL(std::string("stateOn.png"));
                }
            },
            50, 50, 355, 75,
            Colour{0, 0, 0, 0});
}

void LevelCreationScreen::update(double deltaTime) {
    if(countTime) {
        _deltaTime += deltaTime;
    }
    if(savingLevel != nullptr && _deltaTime > 1){
        auto it = std::find(_sprites.begin(), _sprites.end(), savingLevel);
        if (it != _sprites.end()) {
            using std::swap;
            swap(*it, _sprites.back());
            _sprites.pop_back();
        }
        countTime = false;
        _deltaTime = 0;
        callRender();
    }
    _inputFacade->pollEvents();
}

void LevelCreationScreen::update(const KeyEvent& event){
    if(event.getKey() == KEY::KEY_ESCAPE)
    {
        _context->setActiveScreen<MainMenuScreen>();
    }
}

void LevelCreationScreen::update(const MouseEvent& event) {
    _audioFacade->playMusic(_levelBuilder.getSelectedSong().c_str());

    selectedSongText->xPos = 610 - selectedSong.size() * 10;
    selectedSongText->width = selectedSong.size() * 20;
    selectedSongText->text = selectedSong;

    this->callRender();

    if(this->buildTerrainActive) {
        if ((event.getMouseEventType() == MouseEventType::Down || event.getMouseEventType() == MouseEventType::Drag) && event.getMouseClickType() == MouseClickType::Left) {
            _levelBuilder.placeBlock(event.getXPosition(), event.getYPosition());
        }
        if (event.getMouseEventType() == MouseEventType::Down && event.getMouseClickType() == MouseClickType::Right) {
            _levelBuilder.removeBlock(event.getXPosition(), event.getYPosition());
        }
    }
    else{
        if (event.getMouseEventType() == MouseEventType::Down && event.getMouseClickType() == MouseClickType::Left) {
            _levelBuilder.placeSpawnPoint(event.getXPosition(), event.getYPosition());
        }
        if (event.getMouseEventType() == MouseEventType::Down && event.getMouseClickType() == MouseClickType::Right) {
            _levelBuilder.removeSpawnPoint(event.getXPosition(), event.getYPosition());
        }
    }
}

void LevelCreationScreen::callRender() {
    _levelBuilder.drawCurrentScene(_renderList);
    for (auto const &sprite : _sprites) {
        sprite->addToRender(&_renderList);
    }
    _visualFacade->render(_renderList);
}

void LevelCreationScreen::relinkAndSave() {
    //StorageSystem{}.saveWorld(_levelBuilder.getConstructedLevelNonConst());
    LevelStorage{}.saveLevel(_levelBuilder.getConstructedLevel());
}

#include "../../Headers/StateMachine/CharacterSelectionScreen.h"
#include "../../Headers/StateMachine/LevelSelectionScreen.h"
#include "../../Headers/StateMachine/LevelCreationScreen.h"
#include "../../Headers/StateMachine/GameScreen.h"

CharacterSelectionScreen::CharacterSelectionScreen(ScreenStateManager &context, int levelIterator ) : IScreen(context) {
    _inputFacade->getKeyEventObservable().IObservable<KeyEvent>::registerObserver(this);
    auto wallpaper = createShape<ShapeSprite>(1600, 900, 0, 0, "ScreenCharSelection.png");
    wallpaper->layer = 0;
    wallpaper->addToRender(&_renderList);

    _selectedLevelIterator = levelIterator;
    initImages();
    initButtons();
//    _gamelevel = std::make_unique<GameLevel>();
//    _levelManager->loadLevel(levelIterator, *_gamelevel);

    _selectedDifficulty =  createShape<ShapeText>(1300, 135, _difficultyMap[_playerTwoBuilder.getDifficulty()], _difficultyMap[_playerTwoBuilder.getDifficulty()].length()*20, 160, 40, Colour(0, 0, 0, 0));
    _selectedDifficulty->addToRender(&_renderList);

}

void CharacterSelectionScreen::initButtons() {
    // Back
    createShape<SpriteButton>(_inputFacade->getMouseEventObservable(), "",
                              [this]() {
                                  _context->setActiveScreen(std::make_unique<LevelSelectionScreen>(*_context));
                              },
                              120, 120, 15, 15,
                              Colour{0,0,0,0})->addToRender(&_renderList);

    // Player One - White
    createShape<SpriteButton>(_inputFacade->getMouseEventObservable(), "",
                              [this]() {
                                    setFactionColor(_playerOneBuilder, Faction::WHITE);
                              },
                              120, 120, 30, 625,
                              Colour{0,0,0,0})->addToRender(&_renderList);


    // Player One - Red
    createShape<SpriteButton>(_inputFacade->getMouseEventObservable(), "",
                              [this]() {
                                  setFactionColor(_playerOneBuilder, Faction::RED);
                              },
                              120, 120, 180, 625,
                              Colour{0,0,0,0})->addToRender(&_renderList);

    // Player One - Green
    createShape<SpriteButton>(_inputFacade->getMouseEventObservable(), "",
                              [this]() {
                                  setFactionColor(_playerOneBuilder, Faction::GREEN);
                              },
                              120, 120, 320, 625,
                              Colour{0,0,0,0})->addToRender(&_renderList);

    // Player One - Yellow
    createShape<SpriteButton>(_inputFacade->getMouseEventObservable(), "",
                              [this]() {
                                  setFactionColor(_playerOneBuilder, Faction::YELLOW);
                              },
                              120, 120, 460, 625,
                              Colour{0,0,0,0})->addToRender(&_renderList);

    // Player One - Random
    createShape<SpriteButton>(_inputFacade->getMouseEventObservable(), "",
                              [this]() {
                                  setFactionColor(_playerOneBuilder, Faction::RANDOM);
                              },
                              120, 120, 240, 750,
                              Colour{0,0,0,0})->addToRender(&_renderList);


    // Player Two - White
    createShape<SpriteButton>(_inputFacade->getMouseEventObservable(), "",
                              [this]() {
                                if(!_playerTwoBuilder.getIsBot())
                                  setFactionColor(_playerTwoBuilder, Faction::WHITE);
                              },
                              120, 120, 1440, 625,
                              Colour{0,0,0,0})->addToRender(&_renderList);


    // Player Two - Red
    createShape<SpriteButton>(_inputFacade->getMouseEventObservable(), "",
                              [this]() {
                                  if(!_playerTwoBuilder.getIsBot())
                                      setFactionColor(_playerTwoBuilder, Faction::RED);
                              },
                              120, 120, 1300, 625,
                              Colour{0,0,0,0})->addToRender(&_renderList);

    // Player Two - Green
    createShape<SpriteButton>(_inputFacade->getMouseEventObservable(), "",
                              [this]() {
                                  if(!_playerTwoBuilder.getIsBot())
                                      setFactionColor(_playerTwoBuilder, Faction::GREEN);
                              },
                              120, 120, 1160, 625,
                              Colour{0,0,0,0})->addToRender(&_renderList);

    // Player Two - Yellow
    createShape<SpriteButton>(_inputFacade->getMouseEventObservable(), "",
                              [this]() {
                                  if(!_playerTwoBuilder.getIsBot())
                                      setFactionColor(_playerTwoBuilder, Faction::YELLOW);
                              },
                              120, 120, 1020, 625,
                              Colour{0,0,0,0})->addToRender(&_renderList);

    // Player Two - Random
    createShape<SpriteButton>(_inputFacade->getMouseEventObservable(), "",
                              [this]() {
                                  if(!_playerTwoBuilder.getIsBot())
                                      setFactionColor(_playerTwoBuilder, Faction::RANDOM);
                              },
                              120, 120, 1240, 750,
                              Colour{0,0,0,0})->addToRender(&_renderList);


    // Difficulty Lower
    createShape<SpriteButton>(_inputFacade->getMouseEventObservable(), "",
                              [this]() {
                                  _playerTwoBuilder.decreaseDifficulty();
                                  _selectedDifficulty->text = _difficultyMap[_playerTwoBuilder.getDifficulty()];
                              },
                              50, 50, 1190, 125,
                              Colour{0,0,0,0})->addToRender(&_renderList);

    // Difficulty Higher
    createShape<SpriteButton>(_inputFacade->getMouseEventObservable(), "",
                              [this]() {
                                  _playerTwoBuilder.increaseDifficulty();
                                  _selectedDifficulty->text = _difficultyMap[_playerTwoBuilder.getDifficulty()];
                              },
                              50, 50, 1510, 125,
                              Colour{0,0,0,0})->addToRender(&_renderList);

    // Start Game
    createShape<SpriteButton>(_inputFacade->getMouseEventObservable(), "",
                              [this]() {
                                  createShape<ShapeText>(650, 480, "Loading Level...", 0, 340, 45, Colour(255, 255, 255, 0))->addToRender(&_renderList);
                                  //Force an update to render the loading level.
                                  this->update(0);
                                  std::unique_ptr<GameLevel> gameLevel = std::make_unique<GameLevel>();
                                  _levelManager->loadLevel(_selectedLevelIterator, *gameLevel, _playerOneBuilder, _playerTwoBuilder);
                                  _context->setActiveScreen(std::make_unique<GameScreen>(*_context, gameLevel));
                              },
                              450, 120, 540, 350,
                              Colour{0,0,0,0})->addToRender(&_renderList);

    //Toggle AI
    togglePlayerTwoBot = createShape<SpriteButton>(_inputFacade->getMouseEventObservable(), "stateOff.png",
                                                 [this]() {
                                                     bool state = _playerTwoBuilder.getIsBot();
                                                     if (!state) {
                                                         _playerTwoBuilder.setIsBot(true);
                                                         _playerTwoBuilder.setFaction(Faction::RANDOM);
                                                         togglePlayerTwoBot->changeImageURL(std::string("stateOn.png"));
                                                     } else {
                                                         _playerTwoBuilder.setIsBot(false);
                                                         togglePlayerTwoBot->changeImageURL(std::string("stateOff.png"));
                                                     }
                                                 },
                                                 50, 50, 1515, 10,
                                                 Colour{0, 0, 0, 0});
    togglePlayerTwoBot->addToRender(&_renderList);
}

void CharacterSelectionScreen::initImages() {
    _previewMapLeft[Faction::WHITE] = "PlayerW_R0.png";
    _previewMapLeft[Faction::RED] = "PlayerR_R0.png";
    _previewMapLeft[Faction::GREEN] = "PlayerG_R0.png";
    _previewMapLeft[Faction::YELLOW] = "PlayerY_R0.png";
    _previewMapLeft[Faction::RANDOM] = "RandomCharacter.png";

    _previewMapRight[Faction::WHITE] = "PlayerW_L0.png";
    _previewMapRight[Faction::RED] = "PlayerR_L0.png";
    _previewMapRight[Faction::GREEN] = "PlayerG_L0.png";
    _previewMapRight[Faction::YELLOW] = "PlayerY_L0.png";
    _previewMapRight[Faction::RANDOM] = "RandomCharacter.png";

    _difficultyMap[Difficulty::EASY] = "Easy";
    _difficultyMap[Difficulty::MEDIUM] = "Medium";
    _difficultyMap[Difficulty::HARD] = "Hard";

    _leftPreview = createShape<ShapeSprite>(48*2.5, 72*2.5, 240, 270, _previewMapLeft[_playerOneBuilder.getFaction()]);
    _leftPreview->addToRender(&_renderList);

    _rightPreview = createShape<ShapeSprite>(48*2.5, 72*2.5, 1240, 270, _previewMapRight[_playerTwoBuilder.getFaction()]);
    _rightPreview->addToRender(&_renderList);
}

void CharacterSelectionScreen::update(const KeyEvent &event) {
    if(event.getKey() == KEY::KEY_ESCAPE && event.getKeyEventType() == KeyEventType::Up)
    {
        _context->setActiveScreen(std::make_unique<LevelSelectionScreen>(*_context));
    }
}

void CharacterSelectionScreen::update(double deltaTime) {
    _audioFacade->playMusic("menu");
    _inputFacade->pollEvents();
    _renderList.clearLists();

    for (const auto &iterator: _sprites) {
        iterator->addToRender(&_renderList);
    }
    _leftPreview->imageURL = _previewMapLeft[_playerOneBuilder.getFaction()];
    _rightPreview->imageURL = _previewMapRight[_playerTwoBuilder.getFaction()];
    _visualFacade->render(_renderList);
}

void CharacterSelectionScreen::setFactionColor(CharacterBuilder &builder, Faction faction) {
    if(faction == Faction::RANDOM){
        builder.setFaction(faction);
    }
    else if(_playerOneBuilder.getFaction() != faction && _playerTwoBuilder.getFaction() != faction){
        builder.setFaction(faction);
    }
    else{
        _audioFacade->playEffect("negative");
    }
}
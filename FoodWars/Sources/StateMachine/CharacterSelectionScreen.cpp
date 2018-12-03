#include "../../Headers/StateMachine/CharacterSelectionScreen.h"
#include "../../Headers/StateMachine/LevelSelectionScreen.h"
#include "../../Headers/StateMachine/LevelCreationScreen.h"

CharacterSelectionScreen::CharacterSelectionScreen(ScreenStateManager &context, int levelIterator ) : IScreen(context) {
    _inputFacade->getKeyEventObservable().IObservable<KeyEvent>::registerObserver(this);
    auto wallpaper = createShape<ShapeSprite>(1600, 900, 0, 0, "ScreenCharSelection.png");
    wallpaper->layer = 0;
    wallpaper->addToRender(&_renderList);

    _selectedLevelIterator = levelIterator;
    initButtons();
    initImages();
//    _gamelevel = std::make_unique<GameLevel>();
//    _levelManager->loadLevel(levelIterator, *_gamelevel);
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
                                  _playerOneBuilder.setFaction(FACTION::WHITE);
                              },
                              120, 120, 30, 625,
                              Colour{0,0,0,0})->addToRender(&_renderList);


    // Player One - Red
    createShape<SpriteButton>(_inputFacade->getMouseEventObservable(), "",
                              [this]() {
                                  _playerOneBuilder.setFaction(FACTION::RED);
                              },
                              120, 120, 180, 625,
                              Colour{0,0,0,0})->addToRender(&_renderList);

    // Player One - Green
    createShape<SpriteButton>(_inputFacade->getMouseEventObservable(), "",
                              [this]() {
                                  _playerOneBuilder.setFaction(FACTION::GREEN);
                              },
                              120, 120, 320, 625,
                              Colour{0,0,0,0})->addToRender(&_renderList);

    // Player One - Yellow
    createShape<SpriteButton>(_inputFacade->getMouseEventObservable(), "",
                              [this]() {
                                  _playerOneBuilder.setFaction(FACTION::YELLOW);
                              },
                              120, 120, 460, 625,
                              Colour{0,0,0,0})->addToRender(&_renderList);

    // Player One - Random
    createShape<SpriteButton>(_inputFacade->getMouseEventObservable(), "",
                              [this]() {
                                  _playerOneBuilder.setFaction(FACTION::RANDOM);
                              },
                              120, 120, 240, 750,
                              Colour{0,0,0,0})->addToRender(&_renderList);


    // Player Two - White
    createShape<SpriteButton>(_inputFacade->getMouseEventObservable(), "",
                              [this]() {
                                  _playerTwoBuilder.setFaction(FACTION::WHITE);
                              },
                              120, 120, 1440, 625,
                              Colour{0,0,0,0})->addToRender(&_renderList);


    // Player Two - Red
    createShape<SpriteButton>(_inputFacade->getMouseEventObservable(), "",
                              [this]() {
                                  _playerTwoBuilder.setFaction(FACTION::RED);
                              },
                              120, 120, 1300, 625,
                              Colour{0,0,0,0})->addToRender(&_renderList);

    // Player Two - Green
    createShape<SpriteButton>(_inputFacade->getMouseEventObservable(), "",
                              [this]() {
                                  _playerTwoBuilder.setFaction(FACTION::GREEN);
                              },
                              120, 120, 1160, 625,
                              Colour{0,0,0,0})->addToRender(&_renderList);

    // Player Two - Yellow
    createShape<SpriteButton>(_inputFacade->getMouseEventObservable(), "",
                              [this]() {
                                  _playerTwoBuilder.setFaction(FACTION::YELLOW);
                              },
                              120, 120, 1020, 625,
                              Colour{0,0,0,0})->addToRender(&_renderList);

    // Player Two - Random
    createShape<SpriteButton>(_inputFacade->getMouseEventObservable(), "",
                              [this]() {
                                  _playerTwoBuilder.setFaction(FACTION::RANDOM);
                              },
                              120, 120, 1240, 750,
                              Colour{0,0,0,0})->addToRender(&_renderList);


    // Difficulty Lower
    createShape<SpriteButton>(_inputFacade->getMouseEventObservable(), "",
                              [this]() {
                                  _context->setActiveScreen(std::make_unique<LevelSelectionScreen>(*_context));
                              },
                              50, 50, 1190, 125,
                              Colour{0,0,0,0})->addToRender(&_renderList);

    // Difficulty Higher
    createShape<SpriteButton>(_inputFacade->getMouseEventObservable(), "",
                              [this]() {
                                  _context->setActiveScreen(std::make_unique<LevelSelectionScreen>(*_context));
                              },
                              50, 50, 1510, 125,
                              Colour{0,0,0,0})->addToRender(&_renderList);

    // Start Game
    createShape<SpriteButton>(_inputFacade->getMouseEventObservable(), "",
                              [this]() {
                                  _context->setActiveScreen(std::make_unique<LevelSelectionScreen>(*_context));
                              },
                              450, 120, 540, 350,
                              Colour{0,0,0,0})->addToRender(&_renderList);

    //toggleCollidable
    togglePlayerTwoBot = createShape<SpriteButton>(_inputFacade->getMouseEventObservable(), "stateOff.png",
                                                 [this]() {
                                                     bool state = _playerTwoBuilder.getIsBot();
                                                     if (!state) {
                                                         _playerTwoBuilder.setIsBot(true);
                                                         togglePlayerTwoBot->changeImageURL(std::string("stateOn.png"));
                                                     } else {
                                                         _playerTwoBuilder.setIsBot(false);
                                                         togglePlayerTwoBot->changeImageURL(std::string("stateOff.png"));
                                                     }
                                                 },
                                                 50, 50, 1515, 10,
                                                 Colour{0, 0, 0, 0});
    togglePlayerTwoBot->addToRender(&_renderList);;
}

void CharacterSelectionScreen::initImages() {
    _previewMapLeft[FACTION::WHITE] = "PlayerW_R0.png";
    _previewMapLeft[FACTION::RED] = "PlayerR_R0.png";
    _previewMapLeft[FACTION::GREEN] = "PlayerG_R0.png";
    _previewMapLeft[FACTION::YELLOW] = "PlayerY_R0.png";
    _previewMapLeft[FACTION::RANDOM] = "RandomCharacter.png";

    _previewMapRight[FACTION::WHITE] = "PlayerW_L0.png";
    _previewMapRight[FACTION::RED] = "PlayerR_L0.png";
    _previewMapRight[FACTION::GREEN] = "PlayerG_L0.png";
    _previewMapRight[FACTION::YELLOW] = "PlayerY_L0.png";
    _previewMapRight[FACTION::RANDOM] = "RandomCharacter.png";

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
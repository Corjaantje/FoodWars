#include "../../Headers/StateMachine/LevelTransitionScreen.h"
#include "../../Headers/StateMachine/MainMenuScreen.h"

LevelTransitionScreen::LevelTransitionScreen(ScreenStateManager &context, bool playerOneLost, bool playerTwoLost, int scorePlayerOne, int scorePlayerTwo) : IScreen(context){
        _inputFacade->getKeyEventObservable().IObservable<KeyEvent>::registerObserver(this);
        _scorePlayerOne = scorePlayerOne;
        _scorePlayerTwo = scorePlayerTwo;
        setWallpaper(playerOneLost, playerTwoLost);
        //_storageFacade->saveHighscore(scorePlayerOne, _levelManager->getLevelIdentifier());
        _scoreStorer.saveScore(scorePlayerOne, _levelManager->getLevelIdentifier());
        initButtons();
}

void LevelTransitionScreen::setWallpaper(bool playerOneLost, bool playerTwoLost) {
        std::string wallpaperString = "ScreenBlank.png";
        if(playerOneLost && playerTwoLost){
                wallpaperString = "ScreenTransitionDraw.png";
        }
        else if(playerOneLost){
                wallpaperString = "ScreenTransitionLossVic.png";
        }
        else if(playerTwoLost){
                wallpaperString = "ScreenTransitionVicLoss.png";
        }
        auto wallpaper = createShape<ShapeSprite>(1600, 900, 0, 0, wallpaperString);
        wallpaper->layer = 0;
        wallpaper->addToRender(&_renderList);
}

void LevelTransitionScreen::initButtons() {
        // Retry Level
        createShape<SpriteButton>(_inputFacade->getMouseEventObservable(), "",
                                  [this]() {
                                      createShape<ShapeText>(650, 250, "Loading Level...", 0, 340, 45, Colour(255, 255, 255, 0))->addToRender(&_renderList);
                                      //Force an update to render the loading level.
                                      this->update(0);
                                      std::unique_ptr<GameLevel> gameLevel = std::make_unique<GameLevel>();
                                      _levelManager->replayLastLevel(*gameLevel);
                                      _context->setActiveScreen(std::make_unique<GameScreen>(*_context, gameLevel));
                                  },
                                  400, 120, 600, 350,
                                  Colour{0,0,0,0})->addToRender(&_renderList);

        // Next Level
        createShape<SpriteButton>(_inputFacade->getMouseEventObservable(), "",
                                  [this]() {
                                      createShape<ShapeText>(650, 250, "Loading Level...", 0, 340, 45, Colour(255, 255, 255, 0))->addToRender(&_renderList);
                                      //Force an update to render the loading level.
                                      this->update(0);
                                      std::unique_ptr<GameLevel> gameLevel = std::make_unique<GameLevel>();
                                      _levelManager->playNextLevel(*gameLevel);
                                      _context->setActiveScreen(std::make_unique<GameScreen>(*_context, gameLevel));
                                  },
                                  400, 120, 600, 490,
                                  Colour{0,0,0,0})->addToRender(&_renderList);

        // Quit Level
        createShape<SpriteButton>(_inputFacade->getMouseEventObservable(), "",
                                  [this]() {
                                      _context->setActiveScreen<MainMenuScreen>();
                                  },
                                  400, 120, 600, 630,
                                  Colour{0,0,0,0})->addToRender(&_renderList);

        createShape<ShapeText>(300, 315,  std::to_string(_scorePlayerOne), 0, 25*std::to_string(_scorePlayerOne).size(), 45, Colour(255, 255, 255, 0))->addToRender(&_renderList);
        createShape<ShapeText>(1220, 315,  std::to_string(_scorePlayerTwo), 0, 25*std::to_string(_scorePlayerTwo).size(), 45, Colour(255, 255, 255, 0))->addToRender(&_renderList);
}

void LevelTransitionScreen::update(const KeyEvent& event){
        if(event.getKey() == KEY::KEY_ESCAPE)
        {
                _context->setActiveScreen<MainMenuScreen>();
        }
}

void LevelTransitionScreen::update(double deltaTime) {
        _audioFacade->playMusic("menu");
        _inputFacade->pollEvents();
        _renderList.clearLists();

        for (const auto &iterator: _sprites) {
            iterator->addToRender(&_renderList);
        }

        _visualFacade->render(_renderList);
}

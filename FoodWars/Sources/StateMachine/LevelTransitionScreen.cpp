#include "../../Headers/StateMachine/LevelTransitionScreen.h"
#include "../../Headers/StateMachine/MainMenuScreen.h"

LevelTransitionScreen::LevelTransitionScreen(ScreenStateManager &context, bool playerOneLost, bool playerTwoLost, int scorePlayerOne, int scorePlayerTwo) : IScreen(context),
        mouseEventObservable(&_inputFacade->getMouseEventObservable()) {
        keyEventObservable = &_inputFacade->getKeyEventObservable();
        keyEventObservable->IObservable<KeyEvent>::registerObserver(this);
        setWallpaper(playerOneLost, playerTwoLost);
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

LevelTransitionScreen::~LevelTransitionScreen() {

}

void LevelTransitionScreen::initButtons() {
        // Retry Level
        createShape<SpriteButton>(_inputFacade->getMouseEventObservable(), "settings.png",
                                  [this]() {

                                  },
                                  120, 120, 1020, 625,
                                  Colour{0,0,0,0})->addToRender(&_renderList);
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

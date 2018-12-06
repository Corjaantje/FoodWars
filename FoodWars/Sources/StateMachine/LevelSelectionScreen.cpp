#include <utility>

#include "../../Headers/StateMachine/LevelSelectionScreen.h"
#include "../../Headers/StateMachine/MainMenuScreen.h"

LevelSelectionScreen::LevelSelectionScreen(ScreenStateManager& context) :
        IScreen(context),
        mouseEventObservable(&_inputFacade->getMouseEventObservable()),
        _currentIndex(0) {
    _inputFacade->getKeyEventObservable().IObservable<KeyEvent>::registerObserver(this);
    auto wallpaper = createShape<ShapeSprite>(1600, 900, 0, 0, "ScreenLevelSelection.png");
    wallpaper->layer = 0;
    wallpaper->addToRender(&_renderList);

    // MainMenu
    createShape<SpriteButton>(_inputFacade->getMouseEventObservable(), "",
            [c = _context]() {
                c->setActiveScreen<MainMenuScreen>();
            },
            120, 120, 10, 10,
            Colour{0,0,0,0})->addToRender(&_renderList);

    generateLevelButtons();

    createShape<SpriteButton>(_inputFacade->getMouseEventObservable(), "",
            [this]() {
                swapLevels(false);
            },
            60, 60, 535, 444,
            Colour{0,0,0,0})->addToRender(&_renderList);

    createShape<SpriteButton>(_inputFacade->getMouseEventObservable(), "",
            [this]() {
                swapLevels(true);
            },
            60, 60, 1000,444,
            Colour{0,0,0,0})->addToRender(&_renderList);
}

void LevelSelectionScreen::generateLevelButtons() {
    for (const TextButton *button: _levelButtons) {
        delete button;
    }
    _levelButtons.clear();
    _levels = FileManager().getFiles("./Assets/Levels/", {"xml"}, true, false);
    std::sort(_levels.begin(), _levels.end());
    for (int i = 0; i < _levels.size(); i++) {
        TextButton *button = new TextButton{_inputFacade->getMouseEventObservable(),
                                            "Level " + std::to_string(i+1),
                                            [c = _context, this, i]() {
                                                std::unique_ptr<GameLevel> gameLevel = std::make_unique<GameLevel>();
                                                _levelManager->loadLevel(i+1, *gameLevel);
                                                c->setActiveScreen(std::make_unique<GameScreen>(*c, gameLevel));
                                            }, 250, 80, 680, 310 + (i % 3) * 125, Colour(255, 255, 255, 255),
                                            Colour(255, 255, 255, 255)};
        _levelButtons.push_back(button);
        mouseEventObservable->unregisterObserver(button);
    }
    //1, 2
    for (int i = _levels.size() % 3; i <= 3; i++) {
        TextButton *button = new TextButton{_inputFacade->getMouseEventObservable(), "",
                                            []() {}, 250, 80, 680, 310 + i * 125, Colour(255, 255, 255, 255),
                                            Colour(255, 255, 255, 255)};
        _levelButtons.push_back(button);
        mouseEventObservable->unregisterObserver(button);
    }
}

LevelSelectionScreen::~LevelSelectionScreen() {
    for(const TextButton* levelButton: _levelButtons) {
        delete levelButton;
    }
}

void LevelSelectionScreen::update(double deltaTime) {
    _audioFacade->playMusic("menu");
    _inputFacade->pollEvents();
    _renderList.clearLists();

    for (auto &_levelButton : _levelButtons) {
        mouseEventObservable->unregisterObserver(_levelButton);
    }

    for (int i = _currentIndex; i < _currentIndex + 3; i++) {
        _levelButtons[i]->addToRender(&_renderList);
        mouseEventObservable->registerObserver(_levelButtons[i]);
    }

    for (const auto &iterator: _sprites) {
        iterator->addToRender(&_renderList);
    }

    _visualFacade->render(_renderList);
}

void LevelSelectionScreen::swapLevels(bool directionNext) {
    if (directionNext) {
        _currentIndex += 3;
        if (_currentIndex >= _levelButtons.size() - 3)
            _currentIndex = 0;
    } else {
        _currentIndex -= 3;
        if (_currentIndex < 0)
            _currentIndex = _levelButtons.size() - 4;
    }
}


void LevelSelectionScreen::update(const KeyEvent& event){
    if(event.getKey() == KEY::KEY_ESCAPE)
    {
        _context->setActiveScreen<MainMenuScreen>();
    }
}
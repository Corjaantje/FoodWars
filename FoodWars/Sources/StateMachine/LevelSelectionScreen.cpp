#include <utility>

#include "../../Headers/StateMachine/LevelSelectionScreen.h"
#include "../../Headers/StateMachine/MainMenuScreen.h"

LevelSelectionScreen::LevelSelectionScreen(std::shared_ptr<ScreenStateManager> context, std::shared_ptr<LevelManager> levelManager) : IScreen(context), _levelManager(levelManager), _currentIndex(0), mouseEventObservable(_inputFacade->getMouseEventObservable().get()) {
    audioFacade = context->getFacade<AudioFacade>();
    _inputFacade->getKeyEventObservable()->IObservable<KeyEvent>::registerObserver(this);
    _renderList._shapes[0].push_back(createShape<ShapeSprite>(1600, 900, 0, 0, "ScreenLevelSelection.png"));

    // MainMenu
    SpriteButton* quitButton = new SpriteButton {*_inputFacade->getMouseEventObservable(), "", [c = _context]() {  c->setActiveScreen<MainMenuScreen>(); }, 120, 120, 10, 10, Colour{0,0,0,0}};
    quitButton->addToRender(&_renderList);
    _sprites.push_back(quitButton);

    // Highscore
    //TODO ADD HIGHSCORE SCREEN BUTTON
    SpriteButton* highscorebutton = new SpriteButton {*_inputFacade->getMouseEventObservable(), "", [c = _context]() {  c->setActiveScreen<MainMenuScreen>(); }, 120, 120, 150, 10, Colour{0,0,0,0}};
    highscorebutton->addToRender(&_renderList);
    _sprites.push_back(highscorebutton);

    generateLevelButtons();

    SpriteButton* previousButton = new SpriteButton {*_inputFacade->getMouseEventObservable(), "", [this]() {  swapLevels(false); }, 60, 60, 535, 444, Colour{0,0,0,0}};
    previousButton->addToRender(&_renderList);
    _sprites.push_back(previousButton);

    SpriteButton* nextButton = new SpriteButton {*_inputFacade->getMouseEventObservable(), "", [this]() {  swapLevels(true); }, 60, 60, 1000,444, Colour{0,0,0,0}};
    nextButton->addToRender(&_renderList);
    _sprites.push_back(nextButton);
}

void LevelSelectionScreen::generateLevelButtons() {
    for (const TextButton *button: _levelButtons) {
        delete button;
    }
    _levelButtons.clear();
    _currentIndex = 0;
    _levels = FileManager().getFiles("Assets/Levels/", "xml");
    std::sort(_levels.begin(), _levels.end());
    for (int i = 0; i < _levels.size(); i++) {
        int fileNum = std::stoi(_levels[i].substr(5, _levels[i].find('.')));
        TextButton *button = new TextButton{*_inputFacade->getMouseEventObservable(),
                                            "Level " + std::to_string(fileNum + 1),
                                            [c = _context, this, fileNum]() {
                                                c->addOrSetScreenState(
                                                        new GameScreen{c, _levelManager->startLevel(fileNum)});
                                                c->setActiveScreen<GameScreen>();
                                            }, 250, 80, 680, 310 + (i % 3) * 125, Colour(255, 255, 255, 255),
                                            Colour(255, 255, 255, 255)};
        _levelButtons.push_back(button);
        mouseEventObservable->unregisterObserver(button);
    }
    //1, 2
    for (int i = _levels.size() % 3; i <= 3; i++) {
        TextButton *button = new TextButton{*_inputFacade->getMouseEventObservable(), "",
                                            []() {}, 250, 80, 680, 310 + i * 125, Colour(255, 255, 255, 255),
                                            Colour(255, 255, 255, 255)};
        _levelButtons.push_back(button);
        mouseEventObservable->unregisterObserver(button);
    }
}

LevelSelectionScreen::~LevelSelectionScreen() {
    for (IShape *button: _sprites) {
        delete button;
    }
}

void LevelSelectionScreen::update(double deltaTime) {
    audioFacade->playMusic("menu");
    _inputFacade->pollEvents();

    _renderList.clearLists();
    for (auto &_levelButton : _levelButtons) {
        mouseEventObservable->unregisterObserver(_levelButton);
    }

    for(int i = _currentIndex; i < _currentIndex + 3; i++) {
        _levelButtons[i]->addToRender(&_renderList);
        mouseEventObservable->registerObserver(_levelButtons[i]);
    }

    for(const auto &iterator: _sprites) {
        iterator->addToRender(&_renderList);
    }

    visualFacade->render(_renderList);
}

void LevelSelectionScreen::swapLevels(bool directionNext) {
    if(directionNext) {
        _currentIndex += 3;
        if(_currentIndex >= _levelButtons.size() - 3)
            _currentIndex = 0;
    } else {
        _currentIndex -= 3;
        if(_currentIndex < 0)
            _currentIndex = _levelButtons.size() - 4;
    }
}


void LevelSelectionScreen::update(std::shared_ptr<KeyEvent> event){
    if(event->getKey() == KEY::KEY_ESCAPE)
    {
        _context->setActiveScreen<MainMenuScreen>();
    }
}
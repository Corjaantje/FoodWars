#include "../../Headers/StateMachine/HighscoreScreen.h"
#include "../../Headers/StateMachine/MainMenuScreen.h"

HighscoreScreen::HighscoreScreen(ScreenStateManager& context) : IScreen(context),
        _currentIndex{0},
        mouseEventObservable(&_inputFacade->getMouseEventObservable()){
    _inputFacade->getKeyEventObservable().registerKeyEventObserver(this);
    auto wallpaper = createShape<ShapeSprite>(1600, 900, 0, 0, "ScreenHighscore.png");
    wallpaper->layer = 0;
    wallpaper->addToRender(&_renderList);

    createShape<SpriteButton>(_inputFacade->getMouseEventObservable(), "",
            [c = _context]() {
                c->setActiveScreen<MainMenuScreen>();
            },
            140, 140, 12, 12,
            Colour{0,0,0,0})->addToRender(&_renderList);

    createShape<SpriteButton>(_inputFacade->getMouseEventObservable(), "",
                              [this]() {
                                  alterIndex(-1);
                              },
                              60, 60, 535, 444,
                              Colour{0,0,0,0})->addToRender(&_renderList);

    createShape<SpriteButton>(_inputFacade->getMouseEventObservable(), "",
                              [this]() {
                                  alterIndex(1);
                              },
                              60, 60, 1000,444,
                              Colour{0,0,0,0})->addToRender(&_renderList);
    getScoreText();
    Colour textColour = Colour(255, 255, 255, 0);
    for (int i = 0; i < 3 && i < _levelScores.size(); i++)
    {
        placeShape(680, 310 + (i%3 * 125), "", 250, 80, textColour);
    }
}

HighscoreScreen::~HighscoreScreen() = default;


void HighscoreScreen::placeShape(int xpos, int ypos, std::string text, int width, int height, Colour colour) {
    ShapeText* shape = createShape<ShapeText>(xpos, ypos, text, 0, width, height, colour);
    _visualScores.push_back(shape);
}

void HighscoreScreen::update(double deltaTime) {
    _audioFacade->playMusic("menu");
    _inputFacade->pollEvents();

    _renderList.clearLists();

    // todo: determine whether highscores should be reloaded every time they're visited
    getScoreText();
    for (int i = 0; i < 3 && i < _levelScores.size(); i++)
    {
        _visualScores[i]->text = _levelScores[i+_currentIndex][2] + " "+_levelScores[i+_currentIndex][0]+" "+std::to_string(i+1+_currentIndex)+": " +_levelScores[i+_currentIndex][1];
    }
    for (const auto &iterator: _sprites) {
            iterator->addToRender(&_renderList);
    }

    _visualFacade->render(_renderList);
}

void HighscoreScreen::update(const KeyEvent& event){
    if(event.getKey() == KEY::KEY_ESCAPE && event.getKeyEventType() == KeyEventType::Down)
    {
        _context->setActiveScreen<MainMenuScreen>();
    }
}

void HighscoreScreen::getScoreText() {
//    for (const ShapeText *text : _visualScores) {
//        delete text;
//    }
//    _visualScores.clear();
    _levelScores.clear();
    _levelScores = _storageFacade->getHighscoresAndLevels();

//    Colour textColour = Colour(255, 255, 255, 0);
//    for (int i = 0; i < 3 && i < _levelScores.size(); i++)
//    {
//        placeShape(680, 310 + (i%3 * 125), "", 250, 80, textColour);
//    }
}

void HighscoreScreen::alterIndex(int dir) {
    _currentIndex += dir * 3;
    int iCompare = _levelScores.size();

    if (_currentIndex > (iCompare-1)){
        _currentIndex = 0;
    }

    if (_currentIndex < 0) {
        _currentIndex = _levelScores.size() - ((_levelScores.size()) % 3);
        _currentIndex += (_levelScores.size()%3==0) ? -(1*3) : 0;
    }


}

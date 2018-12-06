#include "../../Headers/StateMachine/HighscoreScreen.h"
#include "../../Headers/StateMachine/MainMenuScreen.h"

HighscoreScreen::HighscoreScreen(ScreenStateManager& context) : IScreen(context),
        _currentIndex{0},
        mouseEventObservable(&_inputFacade->getMouseEventObservable()){
    _inputFacade->getKeyEventObservable().registerKeyEventObserver(this);
//    auto wallpaper = createShape<ShapeSprite>(1600, 900, 0, 0, "ScreenHighscore.png");
    auto wallpaper = createShape<ShapeSprite>(1600, 900, 0, 0, "ScreenLevelSelection.png");
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
    generateScoreText();
//    _levelScores = _storageFacade->getHighscoresAndLevels();
//    createShape<ShapeText>(560, 350, "Level 1: ", 0, 200, 85, Colour(255, 255, 255, 0))->addToRender(&_renderList);
//    createShape<ShapeText>(560, 510, "Level 2: ", 0, 200, 85, Colour(255, 255, 255, 0))->addToRender(&_renderList);
//    createShape<ShapeText>(560, 670, "Level 3: ", 0, 200, 85, Colour(255, 255, 255, 0))->addToRender(&_renderList);
//    createShape<ShapeText>(800, 350, _storageFacade->getHighscore(0) + " punten", 0, 250, 85, Colour(255, 255, 255, 0))->addToRender(&_renderList);
//    createShape<ShapeText>(800, 510, _storageFacade->getHighscore(1) + " punten", 0, 250, 85, Colour(255, 255, 255, 0))->addToRender(&_renderList);
//    createShape<ShapeText>(800, 670, _storageFacade->getHighscore(2) + " punten", 0, 250, 85, Colour(255, 255, 255, 0))->addToRender(&_renderList);
}

HighscoreScreen::~HighscoreScreen() = default;



void HighscoreScreen::placeShape(int xpos, int ypos, std::string text, int width, int height, Colour colour) {
    ShapeText* shape = createShape<ShapeText>(xpos, ypos, text, 0, width, height, colour);
    _visualScores.push_back(shape);
    shape->addToRender(&_renderList);
}

void HighscoreScreen::update(double deltaTime) {
    _visualFacade->render(_renderList);
    _audioFacade->playMusic("menu");
    _inputFacade->pollEvents();


}

void HighscoreScreen::update(const KeyEvent& event){
    if(event.getKey() == KEY::KEY_ESCAPE && event.getKeyEventType() == KeyEventType::Down)
    {
        _context->setActiveScreen<MainMenuScreen>();
    }
}

void HighscoreScreen::generateScoreText() {
    for (const ShapeText *text : _visualScores) {
        delete text;
    }
    _levelScores = _storageFacade->getHighscoresAndLevels();


    int uno = YPOSTOP[0];
    int dos = YPOSTOP[1];
    int tres = YPOSTOP[2];

    Colour textColour = Colour(255, 255, 255, 0);
    placeShape(XPOSLEFT, YPOSTOP[0], _levelScores[0+_currentIndex][0]+" "+std::to_string(0+_currentIndex)+":", 200, 85, textColour);
    placeShape(XPOSLEFT, YPOSMID, _levelScores[1+_currentIndex][0]+" "+std::to_string(1+_currentIndex)+":", 200, 85, textColour);
    placeShape(XPOSLEFT, YPOSBOT, _levelScores[2+_currentIndex][0]+" "+std::to_string(2+_currentIndex)+":", 200, 85, textColour);

    placeShape(XPOSRIGHT, YPOSTOP[0], _levelScores[0+_currentIndex][1], 200, 85, textColour);
    placeShape(XPOSRIGHT, YPOSMID, _levelScores[1+_currentIndex][1], 200, 85, textColour);
    placeShape(XPOSRIGHT, YPOSBOT, _levelScores[2+_currentIndex][1], 200, 85, textColour);

}

void HighscoreScreen::alterIndex(int dir) {
    _currentIndex += dir * 3;
    if (_currentIndex > _levelScores.size())
        _currentIndex = 0;

    if (_currentIndex < 0)
        _currentIndex = _levelScores.size() - (((_levelScores.size()-1) % 3)+1);


}

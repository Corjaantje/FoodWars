#include "../../Headers/StateMachine/HighscoreScreen.h"
#include "../../Headers/StateMachine/MainMenuScreen.h"
#include "../../../TonicEngine/Headers/Storage/XMLDeserializationVisitor.h"

HighscoreScreen::HighscoreScreen(ScreenStateManager& context) : IScreen(context),
        _currentIndex{0},
        _mouseEventObservable(&_inputFacade->getMouseEventObservable()){
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
                              60, 60, 280, 510,
                              Colour{0,0,0,0})->addToRender(&_renderList);

    createShape<SpriteButton>(_inputFacade->getMouseEventObservable(), "",
                              [this]() {
                                  alterIndex(1);
                              },
                              60, 60, 1245,510,
                              Colour{0,0,0,0})->addToRender(&_renderList);
    refreshScoreText();
    for (int i = 0; i < 3 && i < _scoreText.size(); i++) {
        placeShape(465, 310 + (i%3 * 175), "", 670, 110, Colour(255, 255, 255, 0));
    }
}

HighscoreScreen::~HighscoreScreen() = default;


void HighscoreScreen::placeShape(int xpos, int ypos, std::string text, int width, int height, Colour colour) {
    auto * shape = createShape<ShapeText>(xpos, ypos, text, 0, width, height, colour);
    _visualScores.push_back(shape);
}

void HighscoreScreen::update(double deltaTime) {
    _audioFacade->playMusic("menu");
    _inputFacade->pollEvents();

    _renderList.clearLists();

    refreshScoreText();
    for (int i = 0; i < 3 && i < _scoreText.size(); i++)
    {
        _visualScores[i]->text = _scoreText[i+_currentIndex];
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

void HighscoreScreen::refreshScoreText() {
    _scoreText.clear();
    XMLReader reader{};
    MyDocument document = reader.LoadFile("./Assets/Highscore.xml");
    DeserializationFactory factory{};
    factory.addType<Highscore>();
    XMLDeserializationVisitor deserializationVisitor{document, factory};
    std::vector<SerializationReceiver *> v;
    deserializationVisitor.visit("highscore", v);
    int i = 0;
    for (SerializationReceiver *receiver: v) {
        Highscore *highscore = dynamic_cast<Highscore *>(receiver);
        if (highscore)
            _scoreText.emplace_back(highscore->getDate()+" Level "+std::to_string(highscore->getID())+": "+std::to_string(highscore->getScore()));// std::vector<std::string>{std::to_string(highscore->getScore()), highscore->getDate()};
        delete highscore;
    }
    //_scoreText = _storageFacade->loadHighscoresForLevels();
}

void HighscoreScreen::alterIndex(int dir) {
    _currentIndex += dir * 3;
    int iCompare = _scoreText.size();

    if (_currentIndex > (iCompare-1)){
        _currentIndex = 0;
    }

    if (_currentIndex < 0) {
        _currentIndex = _scoreText.size() - ((_scoreText.size()) % 3);
        _currentIndex += (_scoreText.size()%3==0) ? -(1*3) : 0;
    }
}
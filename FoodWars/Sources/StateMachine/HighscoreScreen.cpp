#include "../../Headers/StateMachine/HighscoreScreen.h"
#include "../../Headers/StateMachine/MainMenuScreen.h"

HighscoreScreen::HighscoreScreen(std::shared_ptr<ScreenStateManager> context) : IScreen(context) {
    visualFacade = context->getFacade<VisualFacade>();
    audioFacade = context->getFacade<AudioFacade>();
    _storageFacade = context->getFacade<StorageFacade>();
    _inputFacade->getKeyEventObservable()->IObservable<KeyEvent>::registerObserver(this);
    _inputFacade->setWindowResolutionCalculator(_context->getWindowResolutionCalculator());
}

HighscoreScreen::~HighscoreScreen() = default;

void HighscoreScreen::update(double deltaTime) {

    _renderList.clearLists();

    _renderList._shapes[0].push_back(new ShapeSprite{1600, 900, 0, 0, "ScreenHighscore.png"});

    // Backbutton
    SpriteButton* backButton = new SpriteButton {*_inputFacade->getMouseEventObservable(), "", [c = _context]() {  c->setActiveScreen<MainMenuScreen>(); }, 140, 140, 12, 12, Colour{0,0,0,0}};
    backButton->addToRender(&_renderList);
    _sprites.push_back(backButton);
    
    _renderList._shapes[1].push_back(
            createShape<ShapeText>(560, 350, "Level 1: ", 0, 200, 85, Colour(255, 255, 255, 0)));
    _renderList._shapes[1].push_back(
            createShape<ShapeText>(560, 510, "Level 2: ", 0, 200, 85, Colour(255, 255, 255, 0)));
    _renderList._shapes[1].push_back(
            createShape<ShapeText>(560, 670, "Level 3: ", 0, 200, 85, Colour(255, 255, 255, 0)));
    _renderList._shapes[1].push_back(
            createShape<ShapeText>(800, 350, _storageFacade->getHighscore(0) + " punten", 0, 250, 85,
                                   Colour(255, 255, 255, 0)));
    _renderList._shapes[1].push_back(
            createShape<ShapeText>(800, 510, _storageFacade->getHighscore(1) + " punten", 0, 250, 85,
                                   Colour(255, 255, 255, 0)));
    _renderList._shapes[1].push_back(
            createShape<ShapeText>(800, 670, _storageFacade->getHighscore(2) + " punten", 0, 250, 85,
                                   Colour(255, 255, 255, 0)));

    visualFacade->render(_renderList);
    audioFacade->playMusic("menu");
    _inputFacade->pollEvents();
}

void HighscoreScreen::update(std::shared_ptr<KeyEvent> event){
    if(event->getKey() == KEY::KEY_ESCAPE && event->getKeyEventType() == KeyEventType::Down)
    {
        _context->setActiveScreen<MainMenuScreen>();
    }
}

#include "../../Headers/StateMachine/WinTransitionScreen.h"
#include "../../../TonicEngine/Headers/Visual/Shapes/TextButton.h"
#include "../../Headers/StateMachine/GameScreen.h"


WinTransitionScreen::WinTransitionScreen(std::shared_ptr<ScreenStateManager> context) : LevelTransitionScreen(std::move(context)) {
    _renderList._shapes[0].push_back(new ShapeSprite{640, 480, 0, 0, "wallpaper.png"});

    // Next Level
    TextButton* levelSelectionButton = new TextButton {*_inputFacade->getMouseEventObservable(),"Next Level", [c = _context]() {  c->setActiveScreen<GameScreen>(); }, 250, 30, 200, 300};
    levelSelectionButton->addToRender(&_renderList);
    _buttons.push_back(levelSelectionButton);
}

std::string WinTransitionScreen::getScreenName() const {
    return std::string(typeid(WinTransitionScreen).name());
}
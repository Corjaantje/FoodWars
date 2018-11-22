#include "../../Headers/StateMachine/WinTransitionScreen.h"
#include "../../../TonicEngine/Headers/Visual/Shapes/TextButton.h"
#include "../../Headers/StateMachine/GameScreen.h"


WinTransitionScreen::WinTransitionScreen(std::shared_ptr<ScreenStateManager> context) : LevelTransitionScreen(std::move(context)) {
    _renderList._shapes[0].push_back(new ShapeSprite{1600, 900, 0, 0, "ScreenTransitionVictory.png"});

    // Next Level
    _renderList._shapes[1].push_back(createShape<TextButton>(*_inputFacade->getMouseEventObservable(),"", [c = _context]() {  c->setActiveScreen<GameScreen>(); }, 375, 111, 613, 298));
}

std::string WinTransitionScreen::getScreenName() const {
    return std::string(typeid(WinTransitionScreen).name());
}
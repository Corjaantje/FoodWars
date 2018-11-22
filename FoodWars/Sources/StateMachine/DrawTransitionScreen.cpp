#include "../../Headers/StateMachine/DrawTransitionScreen.h"
#include "../../../TonicEngine/Headers/Visual/Shapes/TextButton.h"
#include "../../Headers/StateMachine/GameScreen.h"

DrawTransitionScreen::DrawTransitionScreen(std::shared_ptr<ScreenStateManager> context) : LevelTransitionScreen(std::move(context)) {
    _renderList._shapes[0].push_back(new ShapeSprite{640, 480, 0, 0, "ScreenTransitionDraw.png"});

    // Retry
    _renderList._shapes[1].push_back(createShape<TextButton>(*_inputFacade->getMouseEventObservable(),
            "", [c = _context]() {  c->setActiveScreen<GameScreen>(); }, 375, 111, 613, 298));
}

std::string DrawTransitionScreen::getScreenName() const {
    return std::string(typeid(DrawTransitionScreen).name());
}

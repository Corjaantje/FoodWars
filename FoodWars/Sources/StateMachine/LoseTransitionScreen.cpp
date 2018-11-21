#include "../../Headers/StateMachine/LoseTransitionScreen.h"
#include "../../../TonicEngine/Headers/Visual/Shapes/TextButton.h"
#include "../../Headers/StateMachine/GameScreen.h"

LoseTransitionScreen::LoseTransitionScreen(std::shared_ptr<ScreenStateManager> context) : LevelTransitionScreen(std::move(context)) {
    _renderList._shapes[0].push_back(new ShapeSprite{640, 480, 0, 0, "wallpaper.png"});

    // Retry
    _renderList._shapes[1].push_back(createShape<TextButton>(*_inputFacade->getMouseEventObservable(),
            "Retry", [c = _context]() {  c->setActiveScreen<GameScreen>(); }, 250, 30, 200, 300));
}

std::string LoseTransitionScreen::getScreenName() const {
    return std::string(typeid(LoseTransitionScreen).name());
}

#include "../../Headers/StateMachine/LoseTransitionScreen.h"
#include "../../../TonicEngine/Headers/Visual/Shapes/TextButton.h"
#include "../../Headers/StateMachine/GameScreen.h"

LoseTransitionScreen::LoseTransitionScreen(std::shared_ptr<ScreenStateManager> context) : LevelTransitionScreen(std::move(context)) {
    _renderList._shapes[0].push_back(new ShapeSprite{640, 480, 0, 0, "wallpaper.png"});

    // Retry
    TextButton* retryButton = new TextButton {*_inputFacade->getMouseEventObservable(),"Retry", [c = _context]() {  c->setActiveScreen<GameScreen>(); }, 250, 30, 200, 300};
    retryButton->addToRender(&_renderList);
    _buttons.push_back(retryButton);
}

std::string LoseTransitionScreen::getScreenName() const {
    return std::string(typeid(LoseTransitionScreen).name());
}

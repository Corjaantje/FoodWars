#include "../../Headers/StateMachine/LoseTransitionScreen.h"
#include "../../../TonicEngine/Headers/Visual/Shapes/TextButton.h"
#include "../../Headers/StateMachine/GameScreen.h"

LoseTransitionScreen::LoseTransitionScreen(std::shared_ptr<ScreenStateManager> context) : LevelTransitionScreen(std::move(context)) {
    auto wallpaper = createShape<ShapeSprite>(1600, 900, 0, 0, "ScreenTransitionDefeat.png");
    wallpaper->layer = 0;
    wallpaper->addToRender(&_renderList);

    createShape<TextButton>(*_inputFacade->getMouseEventObservable(), "",
            [c = _context]() {
                c->setActiveScreen<GameScreen>();
            },
            375, 111, 613, 298)->addToRender(&_renderList);

}

std::string LoseTransitionScreen::getScreenName() const {
    return std::string(typeid(LoseTransitionScreen).name());
}

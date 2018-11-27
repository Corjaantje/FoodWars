#include "../../Headers/StateMachine/DrawTransitionScreen.h"
#include "../../../TonicEngine/Headers/Visual/Shapes/TextButton.h"
#include "../../Headers/StateMachine/GameScreen.h"

DrawTransitionScreen::DrawTransitionScreen(std::shared_ptr<ScreenStateManager> context) : LevelTransitionScreen(std::move(context)) {
    auto wallpaper = createShape<ShapeSprite>(640, 480, 0, 0, "ScreenTransitionDraw.png");
    wallpaper->layer = 0;
    wallpaper->addToRender(&_renderList);

    createShape<TextButton>(*_inputFacade->getMouseEventObservable(), "",
            [c = _context]() {
                c->setActiveScreen<GameScreen>();
            },
            375, 111, 613, 298)->addToRender(&_renderList);
}

std::string DrawTransitionScreen::getScreenName() const {
    return std::string(typeid(DrawTransitionScreen).name());
}

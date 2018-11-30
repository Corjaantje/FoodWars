#include "../../Headers/StateMachine/WinTransitionScreen.h"
#include "../../../TonicEngine/Headers/Visual/Shapes/TextButton.h"
#include "../../Headers/StateMachine/GameScreen.h"


WinTransitionScreen::WinTransitionScreen(ScreenStateManager& context) : LevelTransitionScreen(context) {
    auto wallpaper = createShape<ShapeSprite>(1600, 900, 0, 0, "ScreenTransitionVictory.png");
    wallpaper->layer = 0;
    wallpaper->addToRender(&_renderList);

    createShape<TextButton>(_inputFacade->getMouseEventObservable(),"",
            [c = _context]() {
                c->setActiveScreen<GameScreen>();
            },
            375, 111, 613, 298)->addToRender(&_renderList);
}

std::string WinTransitionScreen::getScreenName() const {
    return std::string(typeid(WinTransitionScreen).name());
}
#ifndef PROJECT_SWA_LEVELSELECTIONSCREEN_H
#define PROJECT_SWA_LEVELSELECTIONSCREEN_H

#include "IScreen.h"
#include "../../../TonicEngine/Headers/Visual/Shapes/SpriteButton.h"


class LevelSelectionScreen : public IScreen, public IObserver<KeyEvent> {
public:
    explicit LevelSelectionScreen(std::shared_ptr<ScreenStateManager> context);
    ~LevelSelectionScreen();
    void update(double deltaTime) override;
    void update(std::shared_ptr<KeyEvent> event) override;
};

#endif //PROJECT_SWA_LEVELSELECTIONSCREEN_H
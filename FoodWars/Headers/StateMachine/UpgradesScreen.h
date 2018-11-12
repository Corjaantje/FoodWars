#ifndef PROJECT_SWA_UPGRADESSCREEN_H
#define PROJECT_SWA_UPGRADESSCREEN_H


#include "IScreen.h"
#include "../../../TonicEngine/Headers/Visual/Shapes/SpriteButton.h"

class UpgradesScreen : public IScreen, public IObserver<KeyEvent> {
public:
    explicit UpgradesScreen(std::shared_ptr<ScreenStateManager> context);
    ~UpgradesScreen() override;
    void update(double deltaTime) override;
    void update(std::shared_ptr<KeyEvent> event) override;
};

#endif //PROJECT_SWA_UPGRADESSCREEN_H

#ifndef PROJECT_SWA_PAUSESCREEN_H
#define PROJECT_SWA_PAUSESCREEN_H

#include "IScreen.h"
#include "../../Headers/StateMachine/ScreenStateManager.h"

class PauseScreen : public IScreen {
public:
    explicit PauseScreen(std::shared_ptr<ScreenStateManager> context);
    ~PauseScreen();
    void update(double deltaTime) override;
};
#endif //PROJECT_SWA_PAUSESCREEN_H

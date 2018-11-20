#ifndef PROJECT_SWA_HELPSCREEN_H
#define PROJECT_SWA_HELPSCREEN_H

#include "IScreen.h"

class HelpScreen : public IScreen, public IObserver<KeyEvent> {
public:
    explicit HelpScreen(std::shared_ptr<ScreenStateManager> context);
    ~HelpScreen();
    void update(double deltaTime) override;
    void update(std::shared_ptr<KeyEvent> event) override;
};


#endif //PROJECT_SWA_HELPSCREEN_H

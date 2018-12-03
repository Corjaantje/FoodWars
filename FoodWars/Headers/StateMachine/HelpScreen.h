#ifndef PROJECT_SWA_HELPSCREEN_H
#define PROJECT_SWA_HELPSCREEN_H

#include "IScreen.h"

class HelpScreen : public IScreen, public IObserver<KeyEvent> {
public:
    explicit HelpScreen(ScreenStateManager& context);
    ~HelpScreen();
    void update(double deltaTime) override;
    void update(const KeyEvent& event) override;
};


#endif //PROJECT_SWA_HELPSCREEN_H

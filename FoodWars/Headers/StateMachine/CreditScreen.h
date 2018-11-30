#ifndef PROJECT_SWA_CREDITSCREEN_H
#define PROJECT_SWA_CREDITSCREEN_H

#include "IScreen.h"

class CreditScreen : public IScreen, public IObserver<KeyEvent> {
public:
    explicit CreditScreen(ScreenStateManager& context);
    void update(double deltaTime) override;
    void update(const KeyEvent& event);
};

#endif //PROJECT_SWA_CREDITSCREEN_H

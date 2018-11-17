#ifndef PROJECT_SWA_CREDITSCREEN_H
#define PROJECT_SWA_CREDITSCREEN_H

#include "IScreen.h"

class CreditScreen : public IScreen, public IObserver<KeyEvent> {
public:
    explicit CreditScreen(std::shared_ptr<ScreenStateManager> context);
    ~CreditScreen();
    void update(double deltaTime) override;
    void update(std::shared_ptr<KeyEvent> event);
};

#endif //PROJECT_SWA_CREDITSCREEN_H

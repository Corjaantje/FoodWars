#ifndef PROJECT_SWA_HIGHSCORESCREEN_H
#define PROJECT_SWA_HIGHSCORESCREEN_H

#include "IScreen.h"

class HighscoreScreen : public IScreen, public IObserver<KeyEvent> {
public:
    explicit HighscoreScreen(std::shared_ptr<ScreenStateManager> context);
    ~HighscoreScreen();
    void update(double deltaTime) override;
    void update(std::shared_ptr<KeyEvent> event) override;
};


#endif //PROJECT_SWA_HIGHSCORESCREEN_H

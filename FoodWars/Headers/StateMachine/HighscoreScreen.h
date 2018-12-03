#ifndef PROJECT_SWA_HIGHSCORESCREEN_H
#define PROJECT_SWA_HIGHSCORESCREEN_H

#include "IScreen.h"
#include "../../../TonicEngine/Headers/Storage/StorageFacade.h"

class HighscoreScreen : public IScreen, public IObserver<KeyEvent> {
public:
    explicit HighscoreScreen(ScreenStateManager& context);
    ~HighscoreScreen();
    void update(double deltaTime) override;
    void update(const KeyEvent& event) override;
};


#endif //PROJECT_SWA_HIGHSCORESCREEN_H

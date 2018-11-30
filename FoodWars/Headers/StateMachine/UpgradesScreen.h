#ifndef PROJECT_SWA_UPGRADESSCREEN_H
#define PROJECT_SWA_UPGRADESSCREEN_H


#include "IScreen.h"
#include "../../../TonicEngine/Headers/Visual/Shapes/SpriteButton.h"

class UpgradesScreen : public IScreen, public IObserver<KeyEvent> {
private:
    std::string _previousScreen;
public:
    explicit UpgradesScreen(ScreenStateManager& context);
    ~UpgradesScreen();
    void update(double deltaTime) override;
    void update(const KeyEvent& event) override;
    void setPreviousScreen(const std::string& screenName);
};

#endif //PROJECT_SWA_UPGRADESSCREEN_H

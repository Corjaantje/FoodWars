#ifndef PROJECT_SWA_LEVELTRANSITIONSCREEN_H
#define PROJECT_SWA_LEVELTRANSITIONSCREEN_H

#include "IScreen.h"
#include "../../../TonicEngine/Headers/Visual/Shapes/SpriteButton.h"

class LevelTransitionScreen : public IScreen, public IObserver<KeyEvent> {
public:
    explicit LevelTransitionScreen(ScreenStateManager& context);
    ~LevelTransitionScreen();
    void update(double deltaTime) override;
    void update(const KeyEvent& event) override;
    virtual std::string getScreenName() const = 0;
    void setScore(int score);
};

#endif //PROJECT_SWA_LEVELTRANSITIONSCREEN_H
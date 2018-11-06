#ifndef PROJECT_SWA_LEVELTRANSITIONSCREEN_H
#define PROJECT_SWA_LEVELTRANSITIONSCREEN_H

#include "IScreen.h"
#include "../../../TonicEngine/Headers/Visual/Shapes/SpriteButton.h"

class LevelTransitionScreen : public IScreen, public IObserver<KeyEvent> {
private:
    int _score;
public:
    explicit LevelTransitionScreen(std::shared_ptr<ScreenStateManager> context);
    ~LevelTransitionScreen();
    void update(double deltaTime) override;
    void update(std::shared_ptr<KeyEvent> event) override;
    void setScore(int score){
        _score = score;
    }
    virtual std::string getScreenName() const = 0;
};


#endif //PROJECT_SWA_LEVELTRANSITIONSCREEN_H

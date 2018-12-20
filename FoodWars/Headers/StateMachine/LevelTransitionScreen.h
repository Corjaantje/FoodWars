#ifndef PROJECT_SWA_LEVELTRANSITIONSCREEN_H
#define PROJECT_SWA_LEVELTRANSITIONSCREEN_H


#include "IScreen.h"
#include "../../../TonicEngine/Headers/Events/KeyEvent.h"
#include "../Storage/ScoreStorage.h"


class LevelTransitionScreen : public IScreen, public IObserver<KeyEvent>{
public:
    LevelTransitionScreen(ScreenStateManager& context, bool playerOneLost, bool playerTwoLos, int scorePlayerOne, int scorePlayerTwo);
    ~LevelTransitionScreen() = default;
    void update(double deltaTime) override;
    void update(const KeyEvent& event) override;
private:
    void setWallpaper(bool playerOneLost, bool playerTwoLost);
    void initButtons();
private:
    int _scorePlayerOne;
    int _scorePlayerTwo;
    ScoreStorage _scoreStorer;
};


#endif //PROJECT_SWA_LEVELTRANSITIONSCREEN_H

#ifndef PROJECT_SWA_HIGHSCORESCREEN_H
#define PROJECT_SWA_HIGHSCORESCREEN_H

#include "IScreen.h"
#include "../../../TonicEngine/Headers/Storage/StorageFacade.h"
const int XPOSLEFT = 560;
const int XPOSRIGHT = 800;
const int YPOSTOP[] {350, 510, 670};
const int YPOSMID = 510;
const int YPOSBOT = 670;
const int XPOSOPTIONS[] {680, 940};
const int YPOSOPTIONS[] {310, 435, 560};

class HighscoreScreen : public IScreen, public IObserver<KeyEvent> {
public:
    explicit HighscoreScreen(ScreenStateManager& context);
    ~HighscoreScreen();
    void update(double deltaTime) override;
    void update(const KeyEvent& event) override;

    void generateScoreText();
private:

    void placeShape(int xpos, int ypos, std::string text, int width, int height, Colour colour);
    void alterIndex(int dir);

    int _currentIndex;
    std::vector<std::vector<std::string>> _levelScores;
    std::vector<std::string> _highScores;
    MouseEventObservable* mouseEventObservable;
    std::vector<ShapeText*> _visualScores;
};


#endif //PROJECT_SWA_HIGHSCORESCREEN_H

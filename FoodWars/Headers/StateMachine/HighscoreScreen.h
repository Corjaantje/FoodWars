#ifndef PROJECT_SWA_HIGHSCORESCREEN_H
#define PROJECT_SWA_HIGHSCORESCREEN_H

#include "IScreen.h"
#include "../../../TonicEngine/Headers/Storage/StorageFacade.h"

class Highscore : public SerializationReceiver {
private:
    int _score;
    std::string _date;
public:
    Highscore() : _score{0}, _date{""} {

    }

    Highscore(int score, const std::string &date) : _score{0}, _date{""} {

    }

    int getScore() const {
        return _score;
    };

    std::string getDate() const {
        return _date;
    }

    void accept(SerializationVisitor &visitor) override {
        visitor.visit("score", _score);
        visitor.visit("date", _date);
    }

    string getName() const override {
        return "Highscore";
    }
};

class HighscoreScreen : public IScreen, public IObserver<KeyEvent> {
public:
    explicit HighscoreScreen(ScreenStateManager& context);
    ~HighscoreScreen();
    void update(double deltaTime) override;
    void update(const KeyEvent& event) override;

    void refreshScoreText();
private:

    void placeShape(int xpos, int ypos, std::string text, int width, int height, Colour colour);
    void alterIndex(int dir);

    int _currentIndex;
    std::vector<std::vector<std::string>> _levelScores;
    MouseEventObservable* _mouseEventObservable;
    std::vector<ShapeText*> _visualScores;
};


#endif //PROJECT_SWA_HIGHSCORESCREEN_H

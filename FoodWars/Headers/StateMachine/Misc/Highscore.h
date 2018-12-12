#ifndef PROJECT_SWA_HIGHSCORE_H
#define PROJECT_SWA_HIGHSCORE_H

#include "../../../../TonicEngine/Headers/Storage/SerializationReceiver.h"

class Highscore : public SerializationReceiver {
private:
    int _score;
    std::string _date;
    int _levelID;
public:
    Highscore() : _score{0}, _date{""}, _levelID{0} {

    }

    Highscore(int score, const std::string &date, int ID) : _score{score}, _date{date}, _levelID{ID} {

    }

    int getScore() const {
        return _score;
    };

    void setScore (int newScore)
    {
        _score = newScore;
    }

    std::string getDate() const {
        return _date;
    }

    void setDate(std::string newDate) {
        _date = newDate;
    }

    int getID() const {
        return _levelID;
    }

    void accept(SerializationVisitor &visitor) override {
        visitor.visit("score", _score);
        visitor.visit("date", _date);
        visitor.visit("levelID", _levelID);
    }

    std::string getName() const override {
        return "Highscore";
    }
};

#endif //PROJECT_SWA_HIGHSCORE_H

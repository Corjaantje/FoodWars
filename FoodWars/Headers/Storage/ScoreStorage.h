#ifndef PROJECT_SWA_SCORESTORAGE_H
#define PROJECT_SWA_SCORESTORAGE_H

#include "../StateMachine/Misc/Highscore.h"

const std::string DEFAULT_SCOREPATH = "./Assets/Highscore.xml";
class ScoreStorage {
    public:
    ScoreStorage();

    ~ScoreStorage();

    void saveScore(int score, std::string levelName);
    private:
};


#endif //PROJECT_SWA_SCORESTORAGE_H

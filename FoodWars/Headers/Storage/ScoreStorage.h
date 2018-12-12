#ifndef PROJECT_SWA_SCORESTORAGE_H
#define PROJECT_SWA_SCORESTORAGE_H

#include "../StateMachine/Misc/Highscore.h"

const std::string DEFAULT_XMLPATH = "./Assets/Highscore.xml";
class ScoreStorage {
    public:
    ScoreStorage();

    ~ScoreStorage();

    void loadScore();
    void saveScore(int score, std::string levelName);
    private:
    std::vector<Highscore*> _highscores;
};


#endif //PROJECT_SWA_SCORESTORAGE_H

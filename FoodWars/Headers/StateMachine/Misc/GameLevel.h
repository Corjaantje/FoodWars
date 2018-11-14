#ifndef PROJECT_SWA_GAMELEVEL_H
#define PROJECT_SWA_GAMELEVEL_H


#include "../../GameECS/Entities/EntityManager.h"
#include "Coordinate.h"

class GameLevel {
public:
    GameLevel() = default;
    ~GameLevel() = default;
public:
    EntityManager _entityManager;
    std::string _backgroundMusic;
    std::vector<Coordinate> _spawnPoints;
private:
};


#endif //PROJECT_SWA_GAMELEVEL_H

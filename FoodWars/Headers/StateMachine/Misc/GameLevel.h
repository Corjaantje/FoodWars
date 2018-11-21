#ifndef PROJECT_SWA_GAMELEVEL_H
#define PROJECT_SWA_GAMELEVEL_H


#include "../../GameECS/Entities/EntityManager.h"
#include "Coordinate.h"

class GameLevel {
public:
    GameLevel() = default;
    ~GameLevel() = default;
private:
    EntityManager _entityManager;
    std::string _backgroundMusic;
    std::string _backgroundWallpaper;
    std::vector<Coordinate> _spawnPoints;
public:
    void setEntityManager(EntityManager entityManager);
    void setBackgroundMusic(std::string backgroundMusic);
    void setBackgroundWallpaper(std::string backgroundWallpaper);
    void setSpawnPoints(std::vector<Coordinate> spawnPoints);

    EntityManager getEntityManager() const;
    std::string getBackgroundMusic() const;
    std::string getBackgroundWallpaper() const;
    std::vector<Coordinate> getSpawnPoints() const;
};


#endif //PROJECT_SWA_GAMELEVEL_H

#ifndef PROJECT_SWA_GAMELEVEL_H
#define PROJECT_SWA_GAMELEVEL_H

#include "../../GameECS/Entities/EntityManager.h"
#include "Coordinate.h"
#include "../../Storage/GameLevel/GameLevelSerializationReceiver.h"

// todo: place GameLevel in other directory
class GameLevel : public GameLevelSerializationReceiver {
public:
    GameLevel();

    ~GameLevel() = default;
private:
    EntityManager _entityManager;
    std::string _backgroundMusic;
    std::string _backgroundWallpaper;
    std::vector<Coordinate> _spawnPoints;
public:
    //void setEntityManager(const EntityManager &entityManager);
    void setBackgroundMusic(const std::string &backgroundMusic);

    void setBackgroundWallpaper(const std::string &backgroundWallpaper);

    void setSpawnPoints(const std::vector<Coordinate> &spawnPoints);

    EntityManager& getEntityManager();

    std::string getBackgroundMusic() const;

    std::string getBackgroundWallpaper() const;

    std::vector<Coordinate> getSpawnPoints() const;

    void accept(GameLevelSerializeVisitor &visitor) const override;

    void accept(GameLevelDeserializeVisitor &visitor) override;
};


#endif //PROJECT_SWA_GAMELEVEL_H

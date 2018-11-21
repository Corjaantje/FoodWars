#include <utility>
#include "../../../Headers/StateMachine/Misc/GameLevel.h"

void GameLevel::setBackgroundMusic(std::string backgroundMusic) {
    _backgroundMusic = std::move(backgroundMusic);
}

void GameLevel::setEntityManager(EntityManager entityManager) {
    _entityManager = entityManager;
}

void GameLevel::setSpawnPoints(std::vector<Coordinate> spawnPoints) {
    _spawnPoints = std::move(spawnPoints);
}

void GameLevel::setBackgroundWallpaper(std::string backgroundWallpaper) {
    _backgroundWallpaper = std::move(backgroundWallpaper);
}

std::string GameLevel::getBackgroundWallpaper() const {
    return _backgroundWallpaper;
}

std::string GameLevel::getBackgroundMusic() const {
    return _backgroundMusic;
}

EntityManager GameLevel::getEntityManager() const {
    return _entityManager;
}

std::vector<Coordinate> GameLevel::getSpawnPoints() const {
    return _spawnPoints;
}
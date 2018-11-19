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

std::string GameLevel::getBackgroundMusic() const {
    return _backgroundMusic;
}

EntityManager GameLevel::getEntityManager() const {
    return _entityManager;
}

std::vector<Coordinate> GameLevel::getSpawnPoints() const {
    return _spawnPoints;
}
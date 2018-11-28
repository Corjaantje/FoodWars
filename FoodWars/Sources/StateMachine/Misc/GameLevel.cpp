#include <utility>
#include "../../../Headers/StateMachine/Misc/GameLevel.h"

GameLevel::GameLevel() : _entityManager(), _backgroundMusic(), _backgroundWallpaper(), _spawnPoints() {

}

void GameLevel::setBackgroundMusic(const std::string &backgroundMusic) {
    _backgroundMusic = backgroundMusic;
}


void GameLevel::setSpawnPoints(const std::vector<Coordinate> &spawnPoints) {
    _spawnPoints = spawnPoints;
}

void GameLevel::setBackgroundWallpaper(const std::string &backgroundWallpaper) {
    _backgroundWallpaper = backgroundWallpaper;
}

std::string GameLevel::getBackgroundWallpaper() const {
    return _backgroundWallpaper;
}

std::string GameLevel::getBackgroundMusic() const {
    return _backgroundMusic;
}

EntityManager& GameLevel::getEntityManager() {
    std::cerr << "Get EntityManager in GameLevel should be const!" << std::endl;
    return _entityManager;
}

std::vector<Coordinate> GameLevel::getSpawnPoints() const {
    return _spawnPoints;
}

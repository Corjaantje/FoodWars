#include <utility>
#include <algorithm>
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

void GameLevel::accept(GameLevelSerializeVisitor &visitor) const {
    visitor.visit("backgroundMusic", _backgroundMusic);
    visitor.visit("backgroundWallpaper", _backgroundWallpaper);
    std::vector<SerializationReceiver *> serializableSpawnPoints{_spawnPoints.size()};
    std::vector<Coordinate> coordinates = getSpawnPoints();
    std::transform(coordinates.begin(), coordinates.end(), serializableSpawnPoints.begin(), [](Coordinate &coordinate) {
        return static_cast<SerializationReceiver *>(&coordinate);
    });
    visitor.visit("spawnPoints", serializableSpawnPoints);
    visitor.visit("entityManager", _entityManager);
}

void GameLevel::accept(GameLevelDeserializeVisitor &visitor) {
    visitor.visit("backgroundMusic", _backgroundMusic);
    visitor.visit("backgroundWallpaper", _backgroundWallpaper);
    std::vector<SerializationReceiver *> serializableSpawnPoints{};
    visitor.visit("spawnPoints", serializableSpawnPoints, [spawnPoints = &_spawnPoints]() {
        spawnPoints->push_back(Coordinate{});
        return static_cast<SerializationReceiver *>(&spawnPoints->back());
    });
    visitor.visit("entityManager", _entityManager);
}



#include <utility>

#include "../Headers/LevelLoader.h"
#include "../Headers/GameECS/Components/MoveComponent.h"
#include "../Headers/GameECS/Systems/StorageSystem.h"
#include "../Headers/Storage/LevelStorage.h"
#include "../../TonicEngine/Headers/Storage/FileManager.h"

LevelLoader::LevelLoader() = default;

LevelLoader::~LevelLoader() = default;

GameLevel *LevelLoader::loadLevel(std::string levelPath, GameLevel &gameLevel, CharacterBuilder playerOne, CharacterBuilder playerTwo) {
    /*StorageSystem storage{};
    storage.loadWorld(gameLevel, levelPath);*/
    LevelStorage loader{};
    loader.loadLevel(gameLevel, levelPath);
    if (gameLevel.getSpawnPoints().empty()) {
        return nullptr;
    }
    spawnPlayers(gameLevel,playerOne, playerTwo);

    //Set stats for selected levels
    _lastPlayedLevelPath = levelPath;
    _lastPlayedCharacterOne = playerOne;
    _lastPlayedCharacterTwo = playerTwo;

    // Return gameLevel
    return &gameLevel;
}

void LevelLoader::spawnPlayers(GameLevel &gameLevel, CharacterBuilder playerOne, CharacterBuilder playerTwo) {
    std::vector<Coordinate> spawnPoints = gameLevel.getSpawnPoints();
    EntityManager *entityManager = &gameLevel.getEntityManager();
    int randomNum = rand() % spawnPoints.size();
    int randomNum2 = rand() % spawnPoints.size();
    Coordinate spawnPoint1 = spawnPoints[randomNum];
    while (randomNum == randomNum2) {
        randomNum2 = rand() % spawnPoints.size();
    }
    Coordinate spawnPoint2 = spawnPoints[randomNum2];

    if(playerTwo.getIsBot()){
        playerTwo.setFaction(Faction::RANDOM);
    }
    //Turn RANDOM into a legit faction
    if(playerOne.getFaction() == Faction::RANDOM){
        playerOne.setFaction(static_cast<Faction>(rand() % Faction::RANDOM));
        while(playerOne.getFaction() == playerTwo.getFaction()){
            playerOne.setFaction(static_cast<Faction>(rand() % Faction::RANDOM));
        }
    }
    if(playerTwo.getFaction() == Faction::RANDOM){
        playerTwo.setFaction(static_cast<Faction>(rand() % Faction::RANDOM));
        while(playerTwo.getFaction() == playerOne.getFaction()){
            playerTwo.setFaction(static_cast<Faction>(rand() % Faction::RANDOM));
        }
    }

    playerOne.buildCharacterEntity(gameLevel, 1, spawnPoint1.getXCoord(), spawnPoint1.getYCoord(), true);
    playerTwo.buildCharacterEntity(gameLevel, 2, spawnPoint2.getXCoord(), spawnPoint2.getYCoord(), false);

    int boundLeft = entityManager->createEntity();
    entityManager->addComponentToEntity<BoxCollider>(boundLeft, 900, 900);
    entityManager->addComponentToEntity<PositionComponent>(boundLeft, -900, 0);

    int boundRight = entityManager->createEntity();
    entityManager->addComponentToEntity<BoxCollider>(boundRight, 900, 900);
    entityManager->addComponentToEntity<PositionComponent>(boundRight, 1600, 0);

    int boundBottom = entityManager->createEntity();
    entityManager->addComponentToEntity<BoxCollider>(boundBottom, 1600, 1600);
    entityManager->addComponentToEntity<PositionComponent>(boundBottom, 0, 900);
}

void LevelLoader::replayLastLevel(GameLevel &gameLevel) {
    this->loadLevel(_lastPlayedLevelPath, gameLevel, _lastPlayedCharacterOne, _lastPlayedCharacterTwo);
}

void LevelLoader::playNextLevel(GameLevel &gamelevel) {
    std::string newLevelString;
    std::vector<string> levels = FileManager().getFiles(DEFAULT_XMLPATH, {"xml"}, true, false);
    bool loaded = false;
    for(int i=0; i < levels.size(); i++){
        if(!loaded) {
            //If there is another level around this one
            if (DEFAULT_XMLPATH + levels[i] == _lastPlayedLevelPath && i != levels.size() - 1) {
                loadLevel(DEFAULT_XMLPATH + levels[i + 1], gamelevel, _lastPlayedCharacterOne,
                          _lastPlayedCharacterTwo);
                loaded = true;
                //No level next? Wrap around.
            } else if (DEFAULT_XMLPATH + levels[i] == _lastPlayedLevelPath) {
                loadLevel(DEFAULT_XMLPATH + levels[0], gamelevel, _lastPlayedCharacterOne, _lastPlayedCharacterTwo);
                loaded = true;
            }
        }
    }
}

std::string LevelLoader::getLevelIdentifier() const{
    return _lastPlayedLevelPath;
}

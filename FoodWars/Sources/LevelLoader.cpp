#include "../Headers/LevelLoader.h"
#include "../../TonicEngine/Headers/Visual/Shapes/ShapeRectangle.h"
#include "../Headers/GameECS/Components/MoveComponent.h"
#include "../Headers/GameECS/Components/AnimationComponent.h"
#include "../Headers/GameECS/Components/DamageableComponent.h"
#include "../Headers/GameECS/Systems/StorageSystem.h"
#include "../../TonicEngine/Headers/Visual/Shapes/ShapeSprite.h"
#include "../Headers/GameECS/Components/PlayerComponent.h"

LevelLoader::LevelLoader() = default;

LevelLoader::~LevelLoader() = default;

GameLevel *LevelLoader::loadLevel(int level, GameLevel &gameLevel, CharacterBuilder playerOne, CharacterBuilder playerTwo) {
    StorageSystem storage{};
    std::string levelXML = "Assets/Levels/Level" + std::to_string(level) + ".xml";
    storage.loadWorld(gameLevel, levelXML);
    if (gameLevel.getSpawnPoints().empty()) {
        return nullptr;
    }
    spawnPlayers(gameLevel,playerOne, playerTwo);

    //Set stats for selected levels
    _lastPlayedLevel = level;
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
    this->loadLevel(_lastPlayedLevel, gameLevel, _lastPlayedCharacterOne, _lastPlayedCharacterTwo);
}
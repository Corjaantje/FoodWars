#include "../Headers/LevelLoader.h"
#include "../../TonicEngine/Headers/Visual/Shapes/ShapeRectangle.h"
#include "../Headers/GameECS/Components/MoveComponent.h"
#include "../Headers/GameECS/Components/AnimationComponent.h"
#include "../Headers/GameECS/Components/DamageableComponent.h"
#include "../Headers/GameECS/Systems/StorageSystem.h"
#include "../../TonicEngine/Headers/Visual/Shapes/ShapeSprite.h"

LevelLoader::LevelLoader() = default;

LevelLoader::~LevelLoader() = default;

GameLevel *LevelLoader::loadLevel(int level, GameLevel &gameLevel) {
    StorageSystem storage{};
    std::string levelXML = "Assets/Levels/Level" + std::to_string(level) + ".xml";
    storage.loadWorld(gameLevel, levelXML);
    if (gameLevel.getSpawnPoints().empty()) {
        return nullptr;
    }
    spawnPlayers(gameLevel);
    // Return gameLevel
    return &gameLevel;
}

void LevelLoader::spawnPlayers(GameLevel &gameLevel) {
    std::vector<Coordinate> spawnPoints = gameLevel.getSpawnPoints();
    EntityManager *entityManager = &gameLevel.getEntityManager();
    int randomNum = rand() % spawnPoints.size();
    int randomNum2 = rand() % spawnPoints.size();
    Coordinate spawnPoint1 = spawnPoints[randomNum];
    while (randomNum == randomNum2) {
        randomNum2 = rand() % spawnPoints.size();
    }
    Coordinate spawnPoint2 = spawnPoints[randomNum2];

    // Spawn Location and animation interval
    std::vector<std::unique_ptr<IShape>> spawnAnimation;
    //TODO: replace png depending on teamcomponent
    spawnAnimation.push_back(
            std::make_unique<ShapeSprite>(48, 72, spawnPoint1.getXCoord(), spawnPoint1.getYCoord(), "PlayerW_R0.png"));

    std::vector<std::unique_ptr<IShape>> spawnAnimation2;
    spawnAnimation2.push_back(
            std::make_unique<ShapeSprite>(48, 72, spawnPoint2.getXCoord(), spawnPoint2.getYCoord(), "PlayerG_R0.png"));
    //AnimationComponent animationComponent2{std::move(spawnAnimation2), 0.1};

    // Player
    int player = entityManager->createEntity();
    entityManager->addComponentToEntity<DrawableComponent>(player, std::make_unique<ShapeSprite>(48, 72,
                                                                                                 spawnPoint1.getXCoord(),
                                                                                                 spawnPoint1.getYCoord(),
                                                                                                 "PlayerW_R0.png"));
    entityManager->addComponentToEntity<BoxCollider>(player, 48, 72);
    entityManager->addComponentToEntity<PositionComponent>(player, spawnPoint1.getXCoord(), spawnPoint1.getYCoord());
    auto &turnComponent = entityManager->addComponentToEntity<TurnComponent>(player);
    turnComponent.switchTurn(true);
    turnComponent.setRemainingTime(30);
    entityManager->addComponentToEntity<MoveComponent>(player);
    entityManager->addComponentToEntity<GravityComponent>(player);
    entityManager->addComponentToEntity<AnimationComponent>(player, std::move(spawnAnimation), 0.1);
    entityManager->addComponentToEntity<DamageableComponent>(player);

    // Player
    player = entityManager->createEntity();
    entityManager->addComponentToEntity<DrawableComponent>(player, std::make_unique<ShapeSprite>(48, 72,
                                                                                                 spawnPoint2.getXCoord(),
                                                                                                 spawnPoint2.getYCoord(),
                                                                                                 "PlayerG_R0.png"));
    //entityManager->addComponentToEntity<DrawableComponent>(player, std::make_unique<ShapeSprite>(48, 72, spawnPoint2.getXCoord(), spawnPoint2.getYCoord(), "PlayerG_R0.png"));
    entityManager->addComponentToEntity<BoxCollider>(player, 48, 72);
    entityManager->addComponentToEntity<PositionComponent>(player, spawnPoint2.getXCoord(), spawnPoint2.getYCoord());
    entityManager->addComponentToEntity<TurnComponent>(player);
    entityManager->addComponentToEntity<MoveComponent>(player);
    entityManager->addComponentToEntity<GravityComponent>(player);
    entityManager->addComponentToEntity<AnimationComponent>(player, std::move(spawnAnimation2), 0.1);
    //entityManager->addComponentToEntity<DrawableComponent>(player, entityManager->addComponentToEntity<AnimationComponent>(player, std::move(spawnAnimation2), 0.1));
    entityManager->addComponentToEntity<DamageableComponent>(player);

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
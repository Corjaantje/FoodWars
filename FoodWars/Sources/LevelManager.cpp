#include "../Headers/LevelManager.h"
#include "../../TonicEngine/Headers/Visual/Shapes/ShapeRectangle.h"
#include "../Headers/GameECS/Components/MoveComponent.h"
#include "../Headers/GameECS/Components/AnimationComponent.h"
#include "../Headers/GameECS/Components/DamageableComponent.h"
#include "../Headers/GameECS/Components/DamagingComponent.h"
#include "../Headers/GameECS/Systems/StorageSystem.h"

LevelManager::LevelManager()
{
    _entityManager = EntityManager();
}

LevelManager::~LevelManager() = default;

GameLevel* LevelManager::startLevel(int level) {
    // Load level
    StorageSystem* storage = new StorageSystem();
    _entityManager = EntityManager();
    _gameLevel = storage->loadWorld(_entityManager, "Assets/Levels/Level0.xml");

    if(_gameLevel){
        if(_gameLevel->getSpawnPoints().empty()){
            return nullptr;
        }
        // either choose or delete spawnpoints until you have 2
        spawnPlayers();

    }else
        return nullptr;


    // Return gameLevel
    return _gameLevel;
}

void LevelManager::generateTerrain() {
    for(int y=480; y < 900; y+=32) {
        for (int x=0; x < 1600; x+=32) {
            if ((y % 32 == 0) && (x % 32 == 0)) {
                generateTerrainDrawables(x, y);
            }
        }
    }
    generateTerrainDrawables(0, 480-32);
    generateTerrainDrawables(0, 480-64);
    generateTerrainDrawables(32, 480-32);
    generateTerrainDrawables(1600-32, 480-32);
    generateTerrainDrawables(1600-32, 480-64);
    generateTerrainDrawables(1600-64, 480-32);

}

void LevelManager::generateTerrainDrawables(int x, int y) {
    int randomNum =  rand() % 19 + (-9);
    int randomNum2 = rand() % 19 + (-9);
    int randomNum3 = rand() % 19 + (-9);
    int terrain = _entityManager.createEntity();
    auto *comp = new DrawableComponent();
    _entityManager.addComponentToEntity(terrain, comp);
    _entityManager.addComponentToEntity(terrain, new DamageableComponent { 1 });
    _entityManager.addComponentToEntity(terrain, new BoxCollider{32,32});
    _entityManager.addComponentToEntity(terrain, new PositionComponent(x, y));
    comp->shape = new ShapeRectangle{32, 32, x, y, Colour{149 + randomNum, 69 + randomNum2, 53 + randomNum3, 100}};
}

void LevelManager::spawnPlayers(){
    std::vector<Coordinate> spawnPoints = _gameLevel->getSpawnPoints();
    EntityManager* entityManager = &_gameLevel->getEntityManager();
    int randomNum = rand() % spawnPoints.size();
    int randomNum2 = rand() % spawnPoints.size();
    Coordinate spawnPoint1 = spawnPoints[randomNum];
    while(randomNum == randomNum2){
        randomNum2 = rand() % spawnPoints.size();
    }
    Coordinate spawnPoint2 = spawnPoints[randomNum2];

    // Spawn Location and animation interval
    std::vector<IShape*> spawnAnimation;
    //TODO: replace png depending on teamcomponent
    spawnAnimation.push_back(new ShapeSprite{48, 72, spawnPoint1.getXCoord(), spawnPoint1.getYCoord(), "PlayerW_R0.png"});
    AnimationComponent* animationComponent = new AnimationComponent{spawnAnimation, 0.1};

    std::vector<IShape*> spawnAnimation2;
    spawnAnimation2.push_back(new ShapeSprite{48, 72, spawnPoint2.getXCoord(), spawnPoint2.getYCoord(), "PlayerG_R0.png"});
    AnimationComponent* animationComponent2 = new AnimationComponent{spawnAnimation2, 0.1};

    // TurnComponent
    auto turnComponent = new TurnComponent;
    turnComponent->switchTurn(true);
    turnComponent->setRemainingTime(5);

    // Player
    int player = entityManager->createEntity();
    entityManager->addComponentToEntity(player, new DrawableComponent);
    entityManager->addComponentToEntity(player, new BoxCollider(48, 72));
    entityManager->addComponentToEntity(player, new PositionComponent(spawnPoint1.getXCoord(), spawnPoint1.getYCoord()));
    entityManager->addComponentToEntity(player, turnComponent);
    entityManager->addComponentToEntity(player, new MoveComponent);
    entityManager->addComponentToEntity(player, new GravityComponent());
    entityManager->addComponentToEntity(player, animationComponent);
    entityManager->addComponentToEntity(player, new DamageableComponent);

    // Player
    player = entityManager->createEntity();
    entityManager->addComponentToEntity(player, new DrawableComponent);
    entityManager->addComponentToEntity(player, new BoxCollider(48, 72));
    entityManager->addComponentToEntity(player, new PositionComponent(spawnPoint2.getXCoord(), spawnPoint2.getYCoord()));
    entityManager->addComponentToEntity(player, new TurnComponent);
    entityManager->addComponentToEntity(player, new MoveComponent);
    entityManager->addComponentToEntity(player, new GravityComponent());
    entityManager->addComponentToEntity(player, animationComponent2);
    entityManager->addComponentToEntity(player, new DamageableComponent);

    int boundLeft = entityManager->createEntity();
    entityManager->addComponentToEntity(boundLeft, new BoxCollider(900, 900));
    entityManager->addComponentToEntity(boundLeft, new PositionComponent(-900, 0));

    int boundRight = entityManager->createEntity();
    entityManager->addComponentToEntity(boundRight, new BoxCollider(900, 900));
    entityManager->addComponentToEntity(boundRight, new PositionComponent(1600, 0));

    int boundBottom = entityManager->createEntity();
    entityManager->addComponentToEntity(boundBottom, new BoxCollider(1600, 1600));
    entityManager->addComponentToEntity(boundBottom, new PositionComponent(0, 900));
}
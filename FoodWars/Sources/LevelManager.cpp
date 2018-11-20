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
    // check if spawnpoints.empty > resume game

    // else set players
        // get spawn points
            // choose two spawn points at random


    // Load level
    StorageSystem* storage = new StorageSystem();
    _entityManager = EntityManager();
    _gameLevel = storage->loadWorld(_entityManager, "Assets/Levels/Level12.xml");

    if(_gameLevel){
        if(_gameLevel->getSpawnPoints().empty()){
            return nullptr;
        }
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
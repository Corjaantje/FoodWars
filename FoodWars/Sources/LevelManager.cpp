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
    /*switch(level)
    {
        case 1: {
            _entityManager = EntityManager {};

            int sky = _entityManager.createEntity();
            auto *comp = new DrawableComponent();
            comp->shape = new ShapeRectangle{1600,900,0,0, Colour{173,216,230,0}};
            _entityManager.addComponentToEntity(sky, comp);

            generateTerrain();

            int player = _entityManager.createEntity();

            // Spawn Location and animation interval
            std::vector<IShape*> spawnAnimation;
            spawnAnimation.push_back(new ShapeSprite{48, 72, 32, 300, "PlayerW_R0.png"});
            AnimationComponent* animationComponent = new AnimationComponent{spawnAnimation, 0.1};

            std::vector<IShape*> spawnAnimation2;
            spawnAnimation2.push_back(new ShapeSprite{48, 72, 1500, 300, "PlayerW_L0.png"});
            AnimationComponent* animationComponent2 = new AnimationComponent{spawnAnimation2, 0.1};

            // TurnComponent
            auto turnComponent = new TurnComponent;
            turnComponent->switchTurn(true);
            turnComponent->setRemainingTime(30);

            // Player 1
            _entityManager.addComponentToEntity(player, new DrawableComponent);
            _entityManager.addComponentToEntity(player, new BoxCollider(48, 72));
            _entityManager.addComponentToEntity(player, new PositionComponent(32,0));
            _entityManager.addComponentToEntity(player, turnComponent);
            _entityManager.addComponentToEntity(player, new MoveComponent);
            _entityManager.addComponentToEntity(player, new GravityComponent());
            _entityManager.addComponentToEntity(player, animationComponent);
            _entityManager.addComponentToEntity(player, new DamageableComponent());

            // Player 2
            player = _entityManager.createEntity();
            _entityManager.addComponentToEntity(player, new DrawableComponent);
            _entityManager.addComponentToEntity(player, new BoxCollider(48, 72));
            _entityManager.addComponentToEntity(player, new PositionComponent(576,0));
            _entityManager.addComponentToEntity(player, new TurnComponent);
            _entityManager.addComponentToEntity(player, new MoveComponent);
            _entityManager.addComponentToEntity(player, new GravityComponent());
            _entityManager.addComponentToEntity(player, animationComponent2);
            _entityManager.addComponentToEntity(player, new DamageableComponent());

            int boundOne = _entityManager.createEntity();
            _entityManager.addComponentToEntity(boundOne, new BoxCollider(1600, 1600));
            _entityManager.addComponentToEntity(boundOne, new PositionComponent(-1600, 0));

            int boundTwo = _entityManager.createEntity();
            _entityManager.addComponentToEntity(boundTwo, new BoxCollider(1600, 1600));
            _entityManager.addComponentToEntity(boundTwo, new PositionComponent(1600, 0));

            int boundFour = _entityManager.createEntity();
            _entityManager.addComponentToEntity(boundFour, new BoxCollider(900, 900));
            _entityManager.addComponentToEntity(boundFour, new PositionComponent(0, 900));

            break;
        }
        case 1: {
            StorageSystem* storage = new StorageSystem();
            _entityManager = EntityManager();
            GameLevel* GLHF = storage->loadWorld(_entityManager, "Levels/Level22.xml");
            break;
        }
        default:
            std::cout << "Level does not exist" << std::endl;
            break;
    }*/

    // Load level
    StorageSystem* storage = new StorageSystem();
    _entityManager = EntityManager();
    _gameLevel = storage->loadWorld(_entityManager, "Levels/Level2.xml");

    if(_gameLevel){
        if(_gameLevel->getSpawnPoints().empty()){
            return nullptr;
        }
    }else
        return nullptr;

    int boundLeft = _entityManager.createEntity();
    _entityManager.addComponentToEntity(boundLeft, new BoxCollider(1600, 1600));
    _entityManager.addComponentToEntity(boundLeft, new PositionComponent(-1600, 0));

    int boundRight = _entityManager.createEntity();
    _entityManager.addComponentToEntity(boundRight, new BoxCollider(1600, 1600));
    _entityManager.addComponentToEntity(boundRight, new PositionComponent(1600, 0));

    int boundBottom = _entityManager.createEntity();
    _entityManager.addComponentToEntity(boundBottom, new BoxCollider(900, 900));
    _entityManager.addComponentToEntity(boundBottom, new PositionComponent(0, 900));

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


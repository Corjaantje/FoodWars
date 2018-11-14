#include "../Headers/LevelManager.h"
#include "../../TonicEngine/Headers/Visual/Shapes/ShapeRectangle.h"
#include "../Headers/GameECS/Components/MoveComponent.h"
#include "../Headers/GameECS/Components/AnimationComponent.h"

LevelManager::LevelManager()
{
    _entityManager = EntityManager();
}
LevelManager::~LevelManager() = default;

EntityManager LevelManager::startLevel(int level) {
    switch(level)
    {
        case 1: {
            _entityManager = EntityManager();

            int sky = _entityManager.createEntity();
            auto *comp = new DrawableComponent();
            comp->shape = new ShapeRectangle{1600,900,0,0, Colour{173,216,230,0}};
            _entityManager.addComponentToEntity(sky, comp);

            generateTerrain();

            int player = _entityManager.createEntity();
            std::vector<IShape*> idleAnimation;
            idleAnimation.push_back(new ShapeSprite{48, 72, 32, 300, "PlayerW_R0.png"});
            idleAnimation.push_back(new ShapeSprite{48, 72, 32, 300, "PlayerW_R1.png"});
            idleAnimation.push_back(new ShapeSprite{48, 72, 32, 300, "PlayerW_R2.png"});
            AnimationComponent* animationComponent = new AnimationComponent{idleAnimation, 0.1};

            std::vector<IShape*> idleAnimation2;
            idleAnimation2.push_back(new ShapeSprite{48, 72, 1500, 300, "PlayerL_L0.png"});
            idleAnimation2.push_back(new ShapeSprite{48, 72, 1500, 300, "PlayerL_L1.png"});
            idleAnimation2.push_back(new ShapeSprite{48, 72, 1500, 300, "PlayerL_L2.png"});
            AnimationComponent* animationComponent2 = new AnimationComponent{idleAnimation2, 0.1};

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

            // Player 2
            player = _entityManager.createEntity();
            _entityManager.addComponentToEntity(player, new DrawableComponent);
            _entityManager.addComponentToEntity(player, new BoxCollider(48, 72));
            _entityManager.addComponentToEntity(player, new PositionComponent(576,0));
            _entityManager.addComponentToEntity(player, new TurnComponent);
            _entityManager.addComponentToEntity(player, new MoveComponent);
            _entityManager.addComponentToEntity(player, new GravityComponent());
            _entityManager.addComponentToEntity(player, animationComponent2);

            break;
        }
        default:
            std::cout << "Level does not exist" << std::endl;
            break;
    }
    return _entityManager;
}

void LevelManager::generateTerrain() {
    for(int y=384; y < 900; y+=32) {
        for (int x=0; x < 1600; x+=32) {
            if ((y % 32 == 0) && (x % 32 == 0)) {
                generateTerrainDrawables(x, y);
            }
        }
    }
}

void LevelManager::generateTerrainDrawables(int x, int y) {
    int randomNum =  rand() % 19 + (-9);
    int randomNum2 = rand() % 19 + (-9);
    int randomNum3 = rand() % 19 + (-9);
    int terrain = _entityManager.createEntity();
    auto *comp = new DrawableComponent();
    _entityManager.addComponentToEntity(terrain, comp);
    _entityManager.addComponentToEntity(terrain, new BoxCollider{32,32});
    _entityManager.addComponentToEntity(terrain, new PositionComponent(x, y));
    comp->shape = new ShapeRectangle{32, 32, x, y, Colour{149 + randomNum, 69 + randomNum2, 53 + randomNum3, 100}};
}
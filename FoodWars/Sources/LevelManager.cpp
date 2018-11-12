//
// Created by bryanvanlierop on 11/7/2018.
//

#include "../Headers/LevelManager.h"
#include "../../TonicEngine/Headers/Visual/Shapes/ShapeRectangle.h"
#include "../Headers/GameECS/Components/MoveComponent.h"

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
            comp->shape = std::make_unique<ShapeRectangle>(ShapeRectangle(1600,900,0,0, Colour(173,216,230,0)));
            _entityManager.addComponentToEntity(sky, comp);

            generateTerrain();

            int player = _entityManager.createEntity();
            auto drawablePlayerOne = new DrawableComponent;
            drawablePlayerOne->shape = std::make_unique<ShapeSprite>(ShapeSprite({48, 72, 32, 300, "PlayerW_R0.png"}));
            auto drawablePlayerTwo = new DrawableComponent;
            drawablePlayerTwo->shape = std::make_unique<ShapeSprite>(ShapeSprite(48, 72, 1500, 300, "PlayerL_L1.png"));

            _entityManager.addComponentToEntity(player, drawablePlayerOne);
            _entityManager.addComponentToEntity(player, new BoxCollider(48, 72));
            _entityManager.addComponentToEntity(player, new PositionComponent(32,0));
            auto turnComponent = new TurnComponent;
            turnComponent->switchTurn(true);
            turnComponent->setRemainingTime(30);
            _entityManager.addComponentToEntity(player, turnComponent);
            _entityManager.addComponentToEntity(player, new MoveComponent);
            _entityManager.addComponentToEntity(player, new GravityComponent());

            player = _entityManager.createEntity();
            _entityManager.addComponentToEntity(player, drawablePlayerTwo);
            _entityManager.addComponentToEntity(player, new PositionComponent(576,0));
            _entityManager.addComponentToEntity(player, new TurnComponent);
            _entityManager.addComponentToEntity(player, new MoveComponent);
            _entityManager.addComponentToEntity(player, new BoxCollider(48, 72));
            _entityManager.addComponentToEntity(player, new GravityComponent());
            break;
        }
        default:
            std::cout << "Level does not exist" << std::endl;
            break;
    }
    return _entityManager;
}

void LevelManager::generateTerrain() {
    for(int y=384; y < 900; y+=16) {
        for (int x=0; x < 1600; x+=16) {
            if ((y % 16 == 0) && (x % 16 == 0)) {
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
    _entityManager.addComponentToEntity(terrain, new BoxCollider{16,16});
    _entityManager.addComponentToEntity(terrain, new PositionComponent(x, y));
    comp->shape = std::make_unique<ShapeRectangle>(ShapeRectangle({16, 16, x, y, Colour{149 + randomNum, 69 + randomNum2, 53 + randomNum3, 100}}));
}
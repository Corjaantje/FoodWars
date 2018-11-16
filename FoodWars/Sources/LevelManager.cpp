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

            int boundOne = _entityManager.createEntity();
            _entityManager.addComponentToEntity(boundOne, new BoxCollider(1600, 1600));
            _entityManager.addComponentToEntity(boundOne, new PositionComponent(-1600, 0));

            int boundTwo = _entityManager.createEntity();
            _entityManager.addComponentToEntity(boundTwo, new BoxCollider(1600, 1600));
            _entityManager.addComponentToEntity(boundTwo, new PositionComponent(1600, 0));

            int boundThree = _entityManager.createEntity();
            _entityManager.addComponentToEntity(boundThree, new BoxCollider(900, 900));
            _entityManager.addComponentToEntity(boundThree, new PositionComponent(0, -900));

            int boundFour = _entityManager.createEntity();
            _entityManager.addComponentToEntity(boundFour, new BoxCollider(900, 900));
            _entityManager.addComponentToEntity(boundFour, new PositionComponent(0, 900));
            break;
        }
        default:
            std::cout << "Level does not exist" << std::endl;
            break;
    }
    return _entityManager;
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
    _entityManager.addComponentToEntity(terrain, new BoxCollider{32,32});
    _entityManager.addComponentToEntity(terrain, new PositionComponent(x, y));
    comp->shape = std::make_unique<ShapeRectangle>(ShapeRectangle({32, 32, x, y, Colour{149 + randomNum, 69 + randomNum2, 53 + randomNum3, 100}}));
}
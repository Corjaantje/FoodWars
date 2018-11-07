//
// Created by bryanvanlierop on 11/7/2018.
//

#include "../Headers/LevelManager.h"
#include "../../TonicEngine/Headers/Visual/Shapes/ShapeRectangle.h"

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

            generateTerrain();

            int player = _entityManager.createEntity();
            auto drawablePlayerOne = new DrawableComponent;
            drawablePlayerOne->shape = std::make_unique<ShapeSprite>(ShapeSprite({32, 48, 32, 0, "PlayerW_R0.png"}));
            auto drawablePlayerTwo = new DrawableComponent;
            drawablePlayerTwo->shape = std::make_unique<ShapeSprite>(ShapeSprite(32, 48, 576, 0, "PlayerL_L1.png"));

            _entityManager.addComponentToEntity(player, drawablePlayerOne);
            _entityManager.addComponentToEntity(player, new BoxCollider(32, 48));
            auto turnComponent = new TurnComponent;
            turnComponent->switchTurn(true);
            turnComponent->setRemainingTime(30);
            _entityManager.addComponentToEntity(player, turnComponent);
            _entityManager.addComponentToEntity(player, new GravityComponent());

            player = _entityManager.createEntity();
            _entityManager.addComponentToEntity(player, drawablePlayerTwo);
            _entityManager.addComponentToEntity(player, new TurnComponent);
            _entityManager.addComponentToEntity(player, new BoxCollider(32, 48));
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
    for(int y=112; y < 480; y+=16) {
        for (int x=0; x < 640; x+=16) {
            if (y >= 160 && x >= 528 && x <= 592) {
                generateTerrainDrawables(x, y);
            } else if ((y >= 176 && x >= 496)) {
                generateTerrainDrawables(x, y);
            } else if (y >= 176 && x > 560) {
                generateTerrainDrawables(x, y);
            } else if (y >= 192 && x >= 464) {
                generateTerrainDrawables(x, y);
            } else if (y >= 208 && x >= 432) {
                generateTerrainDrawables(x, y);
            } else if (y >= 224 && x >= 400) {
                generateTerrainDrawables(x, y);
            } else if (y >= 240 && x >= 368) {
                generateTerrainDrawables(x, y);
            } else if (y >= 256 && x >= 336) {
                generateTerrainDrawables(x, y);
            } else if (y >= 192 && x >= 0 && x <= 64 ) {
                generateTerrainDrawables(x, y);
            } else if (y >= 208 && x >= 0 && x <= 96 ) {
                generateTerrainDrawables(x, y);
            } else if (y >= 224 && x >= 0 && x <= 112 ) {
                generateTerrainDrawables(x, y);
            } else if (y >= 256 && x >= 0 && x <= 128 ) {
                generateTerrainDrawables(x, y);
            } else if (y >= 288 ) {
                generateTerrainDrawables(x, y);
            }
        }
    }
}

void LevelManager::generateTerrainDrawables(int x, int y) {
    int randomNum = rand() % 19 + (-9);
    int randomNum2 = rand() % 19 + (-9);
    int randomNum3 = rand() % 19 + (-9);
    int terrain = _entityManager.createEntity();
    DrawableComponent *comp = new DrawableComponent();
    _entityManager.addComponentToEntity(terrain, comp);
    _entityManager.addComponentToEntity(terrain, new BoxCollider{16,16});
    comp->shape = std::make_unique<ShapeRectangle>(ShapeRectangle({16, 16, x, y, Colour{149 + randomNum, 69 + randomNum2, 53 + randomNum3, 100}}));
}
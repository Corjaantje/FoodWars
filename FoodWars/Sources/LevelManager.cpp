//
// Created by bryanvanlierop on 11/7/2018.
//

#include "../Headers/LevelManager.h"

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
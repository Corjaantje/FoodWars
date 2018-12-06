#include "../Headers/PowerupManager.h"
#include "../Headers/GameECS/Components/DrawableComponent.h"
#include "../Headers/GameECS/Components/Collider/BoxCollider.h"
#include "../Headers/GameECS/Components/PositionComponent.h"
#include "../Headers/GameECS/Components/GravityComponent.h"
#include "../../TonicEngine/Headers/Visual/Shapes/ShapeSprite.h"
#include "../Headers/StateMachine/Misc/Coordinate.h"
#include "../Headers/GameECS/Components/PlayerComponent.h"

void PowerupManager::spawnPowerups(EntityManager *entityManager) {
    if (rand() % 2 == 0) {

        int spawnPointX = rand() % 1571;
        int spawnPointY = 0;

        Coordinate spawnPoint;
        spawnPoint.setCoordinates(spawnPointX,spawnPointY);

        // Powerup
        int powerup = entityManager->createEntity();
        entityManager->addComponentToEntity<DrawableComponent>(powerup, std::make_unique<ShapeSprite>(29, 47,
                                                                                                     spawnPoint.getXCoord(),
                                                                                                     spawnPoint.getYCoord(),
                                                                                                     "cake.png"));
        entityManager->addComponentToEntity<BoxCollider>(powerup, 29, 47);
        entityManager->addComponentToEntity<PositionComponent>(powerup, spawnPoint.getXCoord(), spawnPoint.getYCoord());
        entityManager->addComponentToEntity<GravityComponent>(powerup);
    }
}

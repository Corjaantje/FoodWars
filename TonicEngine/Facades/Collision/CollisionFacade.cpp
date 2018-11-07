#include "../../Headers/Collision/CollisionFacade.h"
#include "../../../FoodWars/Headers/GameECS/Components/Collider/BoxColliderComponent.h"

bool CollisionFacade::detectCollision(std::shared_ptr<BoxColliderComponent> collider, PositionComponent boxPosition,
                                      std::map<BoxColliderComponent, PositionComponent> otherColliders){
   /* if (
            recA->position.x + recA->width >= recA->position.x &&
            recB->position.x + recB->width >= recA->position.x &&
            recA->position.y + recA->height >= recB->position.y &&
            recB->position.y + recB->height >= recA->position.y
        )
    {
        return true;
    }*/
    return false;
}
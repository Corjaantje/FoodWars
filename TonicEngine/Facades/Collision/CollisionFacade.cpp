#include "../../Headers/Collision/CollisionFacade.h"
#include "../../../FoodWars/Headers/GameECS/Components/Collider/BoxCollider.h"

bool CollisionFacade::detectCollision(std::shared_ptr<BoxCollider> collider, PositionComponent boxPosition,
                                      std::map<BoxCollider, PositionComponent> otherColliders){
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
#pragma once

#include <memory>
#include <map>
#include "Shape.h"
#include "Rectangle.h"
#include "Circle.h"
#include "../../Facades/IFacade.h"
#include "../../../FoodWars/Headers/GameECS/Components/Collider/BoxColliderComponent.h"
#include "../../../FoodWars/Headers/GameECS/Components/PositionComponent.h"

class CollisionFacade : public IFacade {
public:
    bool detectCollision(std::shared_ptr<BoxColliderComponent> collider, PositionComponent boxPosition, std::map<BoxColliderComponent, PositionComponent> otherColliders);
};

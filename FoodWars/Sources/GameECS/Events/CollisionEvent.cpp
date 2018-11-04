#include "../../../Headers/GameECS/Events/CollisionEvent.h"

int CollisionEvent::getEntity() const {
    return entity;
}

int CollisionEvent::getOtherEntity() const {
    return otherEntity;
}

CollisionEvent::CollisionEvent(int entity, int otherEntity, double collisionAngle) {
    this->entity = entity;
    this->otherEntity = otherEntity;
    this->collisionAngle = collisionAngle;
}

double CollisionEvent::getCollisionAngle() const {
    return collisionAngle;
}




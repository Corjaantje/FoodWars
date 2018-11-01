#include "../../../Headers/GameECS/Events/CollisionEvent.h"

int CollisionEvent::getEntity() const {
    return entity;
}

int CollisionEvent::getOtherEntity() const {
    return otherEntity;
}

CollisionEvent::CollisionEvent(int entity, Direction entityDirection, int otherEntity, Direction otherEntityDirection) {
    this->entity = entity;
    this->entityDirection = entityDirection;
    this->otherEntity = otherEntity;
    this->otherEntityDirection = otherEntityDirection;
}

Direction CollisionEvent::getOtherEntityDirection() const {
    return otherEntityDirection;
}

Direction CollisionEvent::getEntityDirection() const {
    return entityDirection;
}





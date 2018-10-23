#include "../../../Headers/GameECS/Components/MoveComponent.h"

MoveComponent::MoveComponent() : MoveComponent(PositionComponent{}, 0) {
}

MoveComponent::MoveComponent(PositionComponent positionComponent, double velocity) {
    this->positionComponent = positionComponent;
    this->xVelocity = velocity;
    this->yVelocity = velocity;
}

MoveComponent &MoveComponent::operator+=(const MoveComponent &other) {
    positionComponent += other.positionComponent;
    xVelocity += other.xVelocity;
    yVelocity += other.yVelocity;
    return *this;
}

MoveComponent::~MoveComponent() = default;


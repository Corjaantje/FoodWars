#include "../../../Headers/GameECS/Components/MoveComponent.h"

MoveComponent::MoveComponent() : MoveComponent(0) {
}

MoveComponent::MoveComponent(double velocity) {
    this->xVelocity = velocity;
    this->yVelocity = velocity;
}

MoveComponent &MoveComponent::operator+=(const MoveComponent &other) {
    xVelocity += other.xVelocity;
    yVelocity += other.yVelocity;
    return *this;
}

MoveComponent::~MoveComponent() = default;


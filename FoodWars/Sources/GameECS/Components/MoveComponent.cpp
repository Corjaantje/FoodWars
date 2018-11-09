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

std::vector<std::string> MoveComponent::serialize() {
    std::vector<std::string> data;
    data.push_back(std::to_string(xVelocity));
    data.push_back(std::to_string(yVelocity));


    return std::vector<std::string>();
}

MoveComponent::~MoveComponent() = default;


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

std::vector<std::string> MoveComponent::serialize() {
    std::vector<std::string> data;
    data.push_back(std::to_string(xVelocity));
    data.push_back(std::to_string(yVelocity));

    return data;
}

MoveComponent::~MoveComponent() = default;


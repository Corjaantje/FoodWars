#include "../../../Headers/GameECS/Components/MoveComponent.h"

MoveComponent::MoveComponent() : MoveComponent(0) {
}

MoveComponent::MoveComponent(double velocity) : shooting(false) {
    this->xVelocity = velocity;
    this->yVelocity = velocity;
}

MoveComponent::MoveComponent(double xVelocity, double yVelocity) : xVelocity(xVelocity), yVelocity(yVelocity) {

}

MoveComponent &MoveComponent::operator+=(const MoveComponent &other) {
    xVelocity += other.xVelocity;
    yVelocity += other.yVelocity;
    return *this;
}

std::vector<std::string> MoveComponent::serialize() {
    std::vector<std::string> data{};
    data.push_back(std::to_string(xVelocity));
    data.push_back(std::to_string(yVelocity));
    return data;
}

MoveComponent::~MoveComponent() = default;


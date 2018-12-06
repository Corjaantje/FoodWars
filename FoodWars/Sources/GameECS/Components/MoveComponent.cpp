#include "../../../Headers/GameECS/Components/MoveComponent.h"

MoveComponent::MoveComponent() : MoveComponent(0) {
}

MoveComponent::MoveComponent(double velocity) {
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

void MoveComponent::accept(SerializationVisitor &visitor) {
    visitor.visit("xVelocity", xVelocity);
    visitor.visit("yVelocity", yVelocity);
}

MoveComponent::~MoveComponent() = default;


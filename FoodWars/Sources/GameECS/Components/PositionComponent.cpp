#include "../../../Headers/GameECS/Components/PositionComponent.h"

PositionComponent::PositionComponent() : X(0), Y(0) {
}

PositionComponent::PositionComponent(int x, int y) {
    X = x;
    Y = y;
}

PositionComponent &PositionComponent::operator+=(const PositionComponent &other) {
    X += other.X;
    Y += other.Y;
    return *this;
}

PositionComponent &PositionComponent::operator--(int) {
    if(X > 0)
        X--;
    else if(X < 0)
        X++;
    if(Y > 0)
        Y--;
    else if(Y < 0)
        Y++;
    return *this;
}

void PositionComponent::accept(SerializationVisitor &visitor) {
    visitor.visit("x", X);
    visitor.visit("y", Y);
}

std::string PositionComponent::getName() const {
    return "PositionComponent";
}

PositionComponent::PositionComponent(const PositionComponent& other) {
    X = other.X;
    Y = other.Y;
}

PositionComponent &PositionComponent::operator=(const PositionComponent &other) {
    X = other.X;
    Y = other.Y;
    return *this;
}
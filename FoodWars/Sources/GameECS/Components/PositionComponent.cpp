#include "../../../Headers/GameECS/Components/PositionComponent.h"

PositionComponent::PositionComponent() {
    X = 0;
    Y = 0;
}

PositionComponent::PositionComponent(int x, int y) {
    X = x;
    Y = y;
}

PositionComponent &PositionComponent::operator+=(const PositionComponent &other) {
    X += other.X;
    if(X > 20)
        X = 20;
    else if(X < -20)
        X = -20;
    Y += other.Y;
    if(Y > 20)
        Y = 20;
    else if(Y < -20)
        Y = -20;
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

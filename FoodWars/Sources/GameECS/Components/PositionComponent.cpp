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

std::vector<std::string> PositionComponent::serialize() {
    std::vector<std::string> data;
    data.push_back(std::to_string(X));
    data.push_back(std::to_string(Y));


    return data;
}

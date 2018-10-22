#include "../../../Headers/GameECS/Components/PositionComponent.h"

PositionComponent::PositionComponent() {
    X = 0;
    Y = 0;
}

PositionComponent::PositionComponent(int x, int y) {
    X = x;
    Y = y;
}

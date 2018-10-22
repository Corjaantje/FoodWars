#include "../../../Headers/GameECS/Components/MoveComponent.h"

MoveComponent::MoveComponent() {
    positionComponent = PositionComponent();
    velocity = 0;
}

MoveComponent::MoveComponent(PositionComponent positionComponent, double velocity) {
    this->positionComponent = positionComponent;
    this->velocity = velocity;
}

MoveComponent::~MoveComponent() {

}


#include <iostream>
#include "../../../Headers/GameECS/Components/DrawableComponent.h"

DrawableComponent::DrawableComponent() = default;


DrawableComponent::~DrawableComponent() {
    delete shape;
}

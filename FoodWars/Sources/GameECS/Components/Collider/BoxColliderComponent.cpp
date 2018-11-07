#include "../../../../Headers/GameECS/Components/Collider/BoxColliderComponent.h"

BoxColliderComponent::BoxColliderComponent() {
    width = 0;
    height = 0;
}

BoxColliderComponent::BoxColliderComponent(int width, int height) : width(width), height(height) {

}

BoxColliderComponent::~BoxColliderComponent() {

}


#include <iostream>
#include "../../../Headers/GameECS/Components/DrawableComponent.h"

DrawableComponent::DrawableComponent() {

}

DrawableComponent::~DrawableComponent() {

}

void DrawableComponent::draw() {
    std::cout << "X: " << xPos << ",Y: " << yPos << std::endl;
}
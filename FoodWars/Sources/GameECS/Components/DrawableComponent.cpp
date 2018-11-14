#include <iostream>
#include "../../../Headers/GameECS/Components/DrawableComponent.h"

DrawableComponent::DrawableComponent() {

}


DrawableComponent::~DrawableComponent() {

}

std::vector<std::string> DrawableComponent::serialize() {
    std::vector<std::string> data { shape->serialize() };
    // If there are future additions to the things that need to be saved, append them.
    // If placed at the start then more code would  need to be changed.
    return data;
}

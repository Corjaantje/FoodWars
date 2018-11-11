#include <iostream>
#include "../../../Headers/GameECS/Components/DrawableComponent.h"

DrawableComponent::DrawableComponent() {

}


DrawableComponent::~DrawableComponent() {

}

std::vector<std::string> DrawableComponent::serialize() {
    std::vector<std::string> data;
    data.emplace_back("shape");
    data.push_back(std::to_string(shape->xPos));
    data.push_back(std::to_string(shape->yPos));
    data.emplace_back("position");
    data.push_back(std::to_string(shape->getHeight()));
    data.push_back(std::to_string(shape->getWidth()));
    return data;
}

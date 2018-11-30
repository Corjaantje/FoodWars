#include <iostream>
#include "../../../Headers/GameECS/Components/DrawableComponent.h"

DrawableComponent::DrawableComponent(std::unique_ptr<IShape> shape) : _shape(std::move(shape)) {

}

DrawableComponent::~DrawableComponent() = default;

std::vector<std::string> DrawableComponent::serialize() {
    std::vector<std::string> data{_shape->serialize()};
    // If there are future additions to the things that need to be saved, append them.
    // If placed at the start then more code would  need to be changed.
    return data;
}

void DrawableComponent::setShape(IShape *shape) {
    _shape = std::unique_ptr<IShape>(shape);
}

IShape *DrawableComponent::getShape() const {
    return _shape.get();
}

void DrawableComponent::setShape(std::unique_ptr<IShape> shape) {
    _shape = std::move(shape);
}
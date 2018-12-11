#include <iostream>
#include "../../../Headers/GameECS/Components/DrawableComponent.h"

DrawableComponent::DrawableComponent() : DrawableComponent(nullptr) {

}

DrawableComponent::DrawableComponent(std::unique_ptr<IShape> shape) : _shape(std::move(shape)) {

}

DrawableComponent::~DrawableComponent() = default; // warning!


void DrawableComponent::setShape(IShape *shape) {
    _shape = std::unique_ptr<IShape>(shape);
}

IShape *DrawableComponent::getShape() const {
    return _shape.get();
}

void DrawableComponent::setShape(std::unique_ptr<IShape> shape) {
    _shape = std::move(shape);
}

void DrawableComponent::accept(SerializationVisitor &visitor) {
    visitor.visit("shape", _shape.get());
}

void DrawableComponent::accept(DeserializationVisitor &visitor) {
    std::unique_ptr<SerializationReceiver> ptr{nullptr};
    visitor.visit("shape", ptr);
    _shape = std::unique_ptr<IShape>(dynamic_cast<IShape *>(ptr.release()));
}

std::string DrawableComponent::getName() const {
    return "DrawableComponent";
}

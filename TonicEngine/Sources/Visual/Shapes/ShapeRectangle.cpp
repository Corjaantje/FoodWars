#include "../../../Headers/Visual/Shapes/ShapeRectangle.h"
#include "../../../Headers/Visual/Renderlist.h"

ShapeRectangle::ShapeRectangle(const int width, const int height, const int xPos, const int yPos, const Colour colour)
    : IShape(xPos, yPos, 1), width(width), height(height), colour(colour) {
}

ShapeRectangle::~ShapeRectangle() = default;

void ShapeRectangle::addToRender(Renderlist *renderlist) {
    renderlist->_shapes[layer].push_back(this);
}

void ShapeRectangle::render(IRenderer &renderer) const {
    renderer.renderRectangle(*this);
}

void ShapeRectangle::accept(SerializationVisitor &visitor) {
    IShape::accept(visitor);
    visitor.visit("width", width);
    visitor.visit("height", height);
    visitor.visit("colour", colour);
}

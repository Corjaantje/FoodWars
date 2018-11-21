#include "../../../Headers/Visual/Shapes/ShapeRectangle.h"
#include "../../../Headers/Visual/Renderlist.h"

ShapeRectangle::ShapeRectangle(const int width, const int height, const int xPos, const int yPos, const Colour colour)
    : IShape(xPos, yPos), width(width), height(height), colour(colour), layer(1) {
}

ShapeRectangle::~ShapeRectangle() {

}

void ShapeRectangle::addToRender(Renderlist *renderlist) {
    renderlist->_shapes[layer].push_back(this);
}

void ShapeRectangle::render(IRenderer &renderer) const {
    renderer.renderRectangle(*this);
}
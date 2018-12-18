#include "../../../Headers/Visual/Shapes/ShapeRectangle.h"
#include "../../../Headers/Visual/Renderlist.h"

ShapeRectangle::ShapeRectangle() : ShapeRectangle(0, 0, 0, 0, Colour{}) {

}

ShapeRectangle::ShapeRectangle(const int width, const int height, const int xPos, const int yPos, const Colour colour) :
        ShapeRectangle(width, height, xPos, yPos, colour, 1) {
}
ShapeRectangle::ShapeRectangle( int width, int height, int xPos, int yPos, Colour colour, int layer)
        : IShape(xPos, yPos, layer), width(width), height(height), colour(colour) {
}

ShapeRectangle::ShapeRectangle(int width, int height, int xPos, int yPos, Colour colour, int layer) : IShape(xPos, yPos,
                                                                                                             layer),
                                                                                                      width(width),
                                                                                                      height(height),
                                                                                                      colour(colour) {

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

std::string ShapeRectangle::getName() const {
    return "Rectangle";
}
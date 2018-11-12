#include "../../../Headers/Visual/Shapes/ShapeRectangle.h"
#include "../../../Headers/Visual/Renderlist.h"

ShapeRectangle::ShapeRectangle(const int width, const int height, const int xPos, const int yPos, const Colour colour, int layer)
    : IShape(xPos, yPos), width(width), height(height), colour(colour), layer(layer) {
}

ShapeRectangle::~ShapeRectangle() {

}

void ShapeRectangle::addToRender(Renderlist *renderlist) {
    ShapeRectangle rect(width, height, xPos, yPos, colour, layer);
    renderlist->rectangleList.emplace_back(rect);
}
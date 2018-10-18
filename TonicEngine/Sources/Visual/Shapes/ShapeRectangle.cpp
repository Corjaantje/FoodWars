#include "../../../Headers/Visual/Shapes/ShapeRectangle.h"
#include "../../../Headers/Visual/Renderlist.h"

ShapeRectangle::ShapeRectangle(const int width, const int height, const int xPos, const int yPos, const Colour colour) : width(width), height(height), xPos(xPos), yPos(yPos), colour(colour) {
}

ShapeRectangle::~ShapeRectangle() {

}

void ShapeRectangle::addToRender(Renderlist *renderlist) {
    ShapeRectangle rect(width, height, xPos, yPos, colour);
    renderlist->rectangleList.emplace_back(rect);
}
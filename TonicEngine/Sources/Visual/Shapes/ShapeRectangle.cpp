#include "../../../Headers/Visual/Shapes/ShapeRectangle.h"
#include "../../../Headers/Visual/Renderlist.h"

ShapeRectangle::ShapeRectangle(const int width, const int height, const int xPos, const int yPos, const Colour colour) : IShape(xPos, yPos), width(width), height(height), colour(colour) {
}

ShapeRectangle::~ShapeRectangle() {

}

void ShapeRectangle::addToRender(Renderlist *renderlist) {
    ShapeRectangle rect(width, height, xPos, yPos, colour);
    renderlist->rectangleList.emplace_back(rect);
}

std::vector<std::string> ShapeRectangle::serialize() {
    std::vector<std::string> data;
    data.emplace_back("rectangle");
    data.emplace_back("position");
    data.push_back(std::to_string(xPos));
    data.push_back(std::to_string(yPos));
    data.emplace_back("dimensions");
    data.push_back(std::to_string(getHeight()));
    data.push_back(std::to_string(getWidth()));
    data.emplace_back("color");
    data.emplace_back(std::to_string(colour.red));
    data.emplace_back(std::to_string(colour.green));
    data.emplace_back(std::to_string(colour.blue));
    data.emplace_back(std::to_string(colour.alpha));
    return data;
}

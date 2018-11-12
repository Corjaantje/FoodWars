#include "../../../Headers/Visual/Shapes/ShapeText.h"
#include "../../../Headers/Visual/Renderlist.h"

ShapeText::ShapeText(const int x, const int y, std::string string, int fontSize, int width, int height,
                     Colour colour, int layer)
        : IShape(x, y), width(width), height(height), fontSize(fontSize), text(string), colour(colour), layer(layer) {};

ShapeText::~ShapeText() {}

void ShapeText::addToRender(Renderlist *renderlist) {
    ShapeText shape(xPos, yPos, text, fontSize, width, height, colour, layer);
    renderlist->textList.emplace_back(shape);
}

std::string ShapeText::toString() {
    std::string s = std::to_string(xPos) + std::to_string(yPos) + text + std::to_string(fontSize) + std::to_string(width) + std::to_string(height) + std::to_string(colour.red) + std::to_string(colour.green) + std::to_string(colour.blue) + std::to_string(colour.alpha);
    return s;
}
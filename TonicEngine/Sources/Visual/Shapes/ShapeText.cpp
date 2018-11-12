#include "../../../Headers/Visual/Shapes/ShapeText.h"
#include "../../../Headers/Visual/Renderlist.h"

ShapeText::ShapeText(const int x, const int y, std::string string, int fontSize, int width, int height,
                     Colour colour)
        : IShape(x, y), width(width), height(height), fontSize(fontSize), text(string), colour(colour) {};

ShapeText::~ShapeText() {}

void ShapeText::addToRender(Renderlist *renderlist) {
    ShapeText shape(xPos, yPos, text, fontSize, width, height, colour);
    renderlist->textList.emplace_back(shape);
}

std::string ShapeText::toString() {
    std::string s = std::to_string(xPos) + std::to_string(yPos) + text + std::to_string(fontSize) + std::to_string(width) + std::to_string(height) + std::to_string(colour.red) + std::to_string(colour.green) + std::to_string(colour.blue) + std::to_string(colour.alpha);
    return s;
}

std::vector<std::string> ShapeText::serialize() {
    std::vector<std::string> data;
    data.emplace_back("text");
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
    data.emplace_back(text);
    return data;
}

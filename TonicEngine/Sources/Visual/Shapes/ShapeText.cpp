#include "../../../Headers/Visual/Shapes/ShapeText.h"
#include "../../../Headers/Visual/Renderlist.h"

ShapeText::ShapeText(const int x, const int y, const std::string &string, int fontSize, int width, int height,
                     Colour colour)
        : IShape(x, y, 3), width(width), height(height), fontSize(fontSize), text(string), colour(colour) {}

ShapeText::~ShapeText() = default;

void ShapeText::addToRender(Renderlist *renderlist) {
    renderlist->_shapes[layer].push_back(this);
}

std::string ShapeText::toString() {
    std::string s = std::to_string(xPos) + std::to_string(yPos) + text + std::to_string(fontSize) + std::to_string(width) + std::to_string(height) + std::to_string(colour.red) + std::to_string(colour.green) + std::to_string(colour.blue) + std::to_string(colour.alpha);
    return s;
}

void ShapeText::render(IRenderer &renderer) const {
    renderer.renderText(*this);
}

void ShapeText::accept(SerializationVisitor &visitor) {
    IShape::accept(visitor);
    visitor.visit("text", text);
    visitor.visit("fontSize", fontSize);
    visitor.visit("width", width);
    visitor.visit("height", height);
    visitor.visit("colour", colour);
}

std::string ShapeText::getName() const {
    return "Text";
}

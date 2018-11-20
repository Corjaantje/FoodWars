#include "../../../Headers/Visual/Shapes/ShapeLine.h"
#include "../../../Headers/Visual/Renderlist.h"

ShapeLine::ShapeLine(int xPos, int yPos, int xPos2, int yPos2, const Colour& colour)
        : IShape(xPos, yPos), xPos2 {xPos2}, yPos2 {yPos2}, colour{colour}, layer(1) {

}

ShapeLine::~ShapeLine() = default;

void ShapeLine::addToRender(Renderlist *renderlist) {
    renderlist->_shapes[layer].push_back(this);
}

void ShapeLine::render(IRenderer &renderer) const {
    renderer.renderLine(*this);
}

std::vector<std::string> ShapeLine::serialize() {
    return std::vector<std::string>();
}

#include <utility>

#include "../../../Headers/Visual/Shapes/ShapeSprite.h"
#include "../../../Headers/Visual/Renderlist.h"

ShapeSprite::ShapeSprite(int width, int height, int xPos, int yPos, std::string imageURL) : IShape(xPos, yPos), width(width), height(height), imageURL(
        std::move(imageURL)), layer(2) {

}
ShapeSprite::~ShapeSprite() {

}
void ShapeSprite::addToRender(Renderlist *renderlist) {
    renderlist->_shapes[layer].push_back(this);
}

void ShapeSprite::render(IRenderer &renderer) const {
    renderer.renderSprite(*this);
}
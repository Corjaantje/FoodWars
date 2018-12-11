#include <utility>

#include "../../../Headers/Visual/Shapes/ShapeSprite.h"
#include "../../../Headers/Visual/Renderlist.h"

ShapeSprite::ShapeSprite(int width, int height, int xPos, int yPos, const std::string &imageURL) : ShapeSprite(width,
                                                                                                               height,
                                                                                                               xPos,
                                                                                                               yPos,
                                                                                                               imageURL,
                                                                                                               2) {
}

ShapeSprite::ShapeSprite(int width, int height, int xPos, int yPos, const std::string &imageURL, int layer) : IShape(
        xPos, yPos, layer), width(width), height(height), imageURL(imageURL) {

}

ShapeSprite::~ShapeSprite() = default;

void ShapeSprite::addToRender(Renderlist *renderlist) {
    renderlist->_shapes[layer].push_back(this);
}

void ShapeSprite::render(IRenderer &renderer) const {
    renderer.renderSprite(*this);
}

void ShapeSprite::accept(SerializationVisitor &visitor) {
    IShape::accept(visitor);
    visitor.visit("width", width);
    visitor.visit("height", height);
    visitor.visit("imageUrl", imageURL);
}

std::string ShapeSprite::getName() const {
    return "Sprite";
}

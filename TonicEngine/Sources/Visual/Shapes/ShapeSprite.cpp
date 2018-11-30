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

std::vector<std::string> ShapeSprite::serialize() {
    std::vector<std::string> data;
    data.emplace_back("sprite");
    data.emplace_back("position");
    data.push_back(std::to_string(xPos));
    data.push_back(std::to_string(yPos));
    data.emplace_back("dimensions");
    data.push_back(std::to_string(getHeight()));
    data.push_back(std::to_string(getWidth()));
    data.emplace_back("image");
    data.emplace_back(imageURL);
    data.emplace_back("layer");
    data.emplace_back(std::to_string(layer));
    return data;
}

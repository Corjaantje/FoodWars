#include <utility>

#include "../../../Headers/Visual/Shapes/ShapeSprite.h"
#include "../../../Headers/Visual/Renderlist.h"

ShapeSprite::ShapeSprite(int width, int height, int xPos, int yPos, std::string imageURL) : IShape(xPos, yPos), width(width), height(height), imageURL(
        std::move(imageURL)) {

}
ShapeSprite::~ShapeSprite() {

}
void ShapeSprite::addToRender(Renderlist *renderlist) {
    ShapeSprite sprite(width, height, xPos, yPos, imageURL);
    renderlist->spriteList.emplace_back(sprite);
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
    return data;
}

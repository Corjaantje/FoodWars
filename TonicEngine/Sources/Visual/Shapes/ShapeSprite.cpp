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
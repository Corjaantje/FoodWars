#include <utility>

#include "../../Headers/Visual/ShapeSprite.h"

ShapeSprite::ShapeSprite(int width, int height, int xPos, int yPos, std::string imageURL) : width(width), height(height), xPos(xPos), yPos(yPos), imageURL(
        std::move(imageURL)) {

}
ShapeSprite::~ShapeSprite() {

}
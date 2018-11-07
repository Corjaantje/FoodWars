#include "../../Headers/Visual/Renderlist.h"

void Renderlist::mergeShapeRectangles(std::vector<ShapeRectangle> _rectangleList) {
    for(int i = 0; i < _rectangleList.size(); i++){
        rectangleList.push_back(_rectangleList[i]);
    }
}

void Renderlist::mergeShapeSprites(std::vector<ShapeSprite> _spriteList) {
    for(int i = 0; i < _spriteList.size(); i++){
        spriteList.push_back(_spriteList[i]);
    }
}

void Renderlist::mergeShapeText(std::vector<ShapeText> _textList) {
    for(int i = 0; i < _textList.size(); i++){
        textList.push_back(_textList[i]);
    }
}
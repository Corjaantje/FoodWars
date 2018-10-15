#ifndef PROJECT_SWA_SHAPESPRITE_H
#define PROJECT_SWA_SHAPESPRITE_H


#include <string>

class ShapeSprite {
public:
    ShapeSprite(int width, int height, int xPos, int yPos, std::string imageURL);
    ~ShapeSprite();
public:
    int width;
    int height;
    int xPos;
    int yPos;
    std::string imageURL;
};


#endif //PROJECT_SWA_SHAPESPRITE_H

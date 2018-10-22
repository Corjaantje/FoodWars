#ifndef PROJECT_SWA_SHAPESPRITE_H
#define PROJECT_SWA_SHAPESPRITE_H


#include <string>
#include "IShape.h"

class ShapeSprite : public IShape {
public:
    ShapeSprite(int width, int height, int xPos, int yPos, std::string imageURL);
    ~ShapeSprite() override;
    void addToRender(Renderlist* renderlist) override;
public:
    int width;
    int height;
    std::string imageURL;
};


#endif //PROJECT_SWA_SHAPESPRITE_H

#ifndef PROJECT_SWA_SHAPESPRITE_H
#define PROJECT_SWA_SHAPESPRITE_H


#include <string>
#include "IShape.h"

class ShapeSprite : public IShape {
public:
    ShapeSprite(int width, int height, int xPos, int yPos, std::string imageURL);
    ~ShapeSprite() override;
    void addToRender(Renderlist* renderlist) override;
    void render(IRenderer &renderer) const override;
public:
    int width;
    int height;
    std::string imageURL;
    int layer;
};


#endif //PROJECT_SWA_SHAPESPRITE_H

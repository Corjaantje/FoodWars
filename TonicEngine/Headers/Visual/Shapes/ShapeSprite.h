#ifndef PROJECT_SWA_SHAPESPRITE_H
#define PROJECT_SWA_SHAPESPRITE_H


#include <string>
#include "IShape.h"

class ShapeSprite : public IShape {
public:
    ShapeSprite(int width, int height, int xPos, int yPos, const std::string &imageURL);

    ShapeSprite(int width, int height, int xPos, int yPos, const std::string &imageURL, int layer);
    ~ShapeSprite() override;
    void addToRender(Renderlist* renderlist) override;
    void render(IRenderer &renderer) const override;
public:
    int width;
    int height;
    std::string imageURL;

    int getWidth() const override { return width; }
    int getHeight() const override { return height; }

    void accept(SerializationVisitor &visitor) override;

    std::string getName() const override;
};


#endif //PROJECT_SWA_SHAPESPRITE_H

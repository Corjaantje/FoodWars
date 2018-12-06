#ifndef PROJECT_SWA_SHAPELINE_H
#define PROJECT_SWA_SHAPELINE_H

#include "IShape.h"
#include "../Colour.h"

class ShapeLine : public IShape {
public:
    ShapeLine();
    ShapeLine(int xPos, int yPos, int xPos2, int yPos2, const Colour& colour);
    ~ShapeLine() override;
    void addToRender(Renderlist* renderlist) override;
public:
    Colour colour;
    int xPos2, yPos2;
    void render(IRenderer &renderer) const override;
    int getWidth() const override  { return 0; }
    int getHeight() const override { return 0; }

    void accept(SerializationVisitor &visitor) override;

};
#endif //PROJECT_SWA_SHAPELINE_H

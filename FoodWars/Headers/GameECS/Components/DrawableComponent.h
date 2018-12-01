#ifndef PROJECT_SWA_DRAWABLECOMPONENT_H
#define PROJECT_SWA_DRAWABLECOMPONENT_H

#include <bits/unique_ptr.h>
#include "Component.h"
#include "../../../../TonicEngine/Headers/Visual/Shapes/IShape.h"
#include "../../../../TonicEngine/Headers/Storage/ISerializable.h"

class DrawableComponent: public Component, public ISerializable {
private:
    std::unique_ptr<IShape> _shape;
public:
    explicit DrawableComponent(std::unique_ptr<IShape> shape);
    ~DrawableComponent() override;
    std::vector<std::string> serialize() override;

    void setShape(IShape *shape);

    void setShape(std::unique_ptr<IShape> shape);

    virtual IShape *getShape() const;
};


#endif //PROJECT_SWA_DRAWABLECOMPONENT_H

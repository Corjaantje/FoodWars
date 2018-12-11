#ifndef PROJECT_SWA_DRAWABLECOMPONENT_H
#define PROJECT_SWA_DRAWABLECOMPONENT_H

#include <memory>
#include "Component.h"
#include "../../../../TonicEngine/Headers/Visual/Shapes/IShape.h"
#include "../../../../TonicEngine/Headers/Storage/ISerializable.h"

class DrawableComponent : public Component {
private:
    std::unique_ptr<IShape> _shape;
public:
    explicit DrawableComponent(std::unique_ptr<IShape> shape);
    ~DrawableComponent() override;

    void setShape(IShape *shape);

    void setShape(std::unique_ptr<IShape> shape);

    virtual IShape *getShape() const;

    void accept(SerializationVisitor &visitor) override;

    std::string getName() const override;
};


#endif //PROJECT_SWA_DRAWABLECOMPONENT_H

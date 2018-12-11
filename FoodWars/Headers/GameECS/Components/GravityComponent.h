#ifndef PROJECT_SWA_GRAVITYCOMPONENT_H
#define PROJECT_SWA_GRAVITYCOMPONENT_H

#include "Component.h"
#include "../../../../TonicEngine/Headers/Storage/ISerializable.h"

class GravityComponent : public Component {
public:
    double gravityApplied;
    GravityComponent();
    explicit GravityComponent(double gravity);

    void accept(SerializationVisitor &visitor) override;

    std::string getName() const override;
};

#endif //PROJECT_SWA_GRAVITYCOMPONENT_H

#ifndef PROJECT_SWA_MOVECOMPONENT_H
#define PROJECT_SWA_MOVECOMPONENT_H

#include "PositionComponent.h"
#include "Component.h"
#include "../../../../TonicEngine/Headers/Storage/ISerializable.h"

class MoveComponent : public Component {
public:
    double xVelocity;
    double yVelocity;
    MoveComponent();
    explicit MoveComponent(double velocity);

    MoveComponent(double xVelocity, double yVelocity);
    MoveComponent& operator+=(const MoveComponent& other);
    ~MoveComponent() override;

    void accept(SerializationVisitor &visitor) override;
};

#endif //PROJECT_SWA_MOVECOMPONENT_H

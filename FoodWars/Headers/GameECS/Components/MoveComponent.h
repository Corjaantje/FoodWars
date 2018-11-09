

#ifndef PROJECT_SWA_MOVECOMPONENT_H
#define PROJECT_SWA_MOVECOMPONENT_H

#include "PositionComponent.h"
#include "Component.h"
#include "../../../../TonicEngine/Headers/Storage/ISerializable.h"

class MoveComponent : public Component, public ISerializable {
public:
    PositionComponent positionComponent;
    double xVelocity;
    double yVelocity;
    MoveComponent();
    MoveComponent(PositionComponent positionComponent, double velocity);
    MoveComponent& operator+=(const MoveComponent& other);
    ~MoveComponent() override;
    std::vector<std::string> serialize() override;
};

#endif //PROJECT_SWA_MOVECOMPONENT_H

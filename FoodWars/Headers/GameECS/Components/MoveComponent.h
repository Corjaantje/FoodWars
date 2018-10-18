

#ifndef PROJECT_SWA_MOVECOMPONENT_H
#define PROJECT_SWA_MOVECOMPONENT_H

#include "PositionComponent.h"
#include "Component.h"

class MoveComponent : public Component {
public:
    PositionComponent positionComponent;
    double velocity;
    MoveComponent();
    MoveComponent(PositionComponent positionComponent, double velocity);
    ~MoveComponent() override;
};

#endif //PROJECT_SWA_MOVECOMPONENT_H

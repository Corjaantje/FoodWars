#ifndef PROJECT_SWA_MOVECOMPONENT_H
#define PROJECT_SWA_MOVECOMPONENT_H

#include "PositionComponent.h"
#include "Component.h"

class MoveComponent : public Component {
public:
    double xVelocity;
    double yVelocity;
    MoveComponent();
    explicit MoveComponent(double velocity);
    MoveComponent& operator+=(const MoveComponent& other);
    ~MoveComponent() override;
};

#endif //PROJECT_SWA_MOVECOMPONENT_H

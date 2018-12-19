#ifndef PROJECT_SWA_POSITIONCOMPONENT_H
#define PROJECT_SWA_POSITIONCOMPONENT_H

#include "Component.h"
#include "../../../../TonicEngine/Headers/Storage/ISerializable.h"

class PositionComponent : public Component {
public:
    int X;
    int Y;

    PositionComponent();

    PositionComponent(int x, int y);

    PositionComponent &operator=(const PositionComponent &other);
    PositionComponent& operator+=(const PositionComponent& other);
    PositionComponent& operator--(int);
    PositionComponent(const PositionComponent& other);

    void accept(SerializationVisitor &visitor) override;

    std::string getName() const override;
};

#endif //PROJECT_SWA_POSITIONCOMPONENT_H
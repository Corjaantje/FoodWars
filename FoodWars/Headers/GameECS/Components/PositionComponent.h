#include "Component.h"

#include "../../../../TonicEngine/Headers/Storage/ISerializable.h"

class PositionComponent: public ISerializable {
public:
    int X;
    int Y;
    PositionComponent();
    PositionComponent(int x, int y);
    PositionComponent& operator+=(const PositionComponent& other);
    PositionComponent& operator--(int);
    std::vector<std::string> serialize() override;
};
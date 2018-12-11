#include "Component.h"
#include "../../../../TonicEngine/Headers/Storage/ISerializable.h"

class PositionComponent : public Component {
public:
    int X;
    int Y;
    PositionComponent();
    PositionComponent(int x, int y);
    PositionComponent& operator+=(const PositionComponent& other);
    PositionComponent& operator--(int);

    void accept(SerializationVisitor &visitor) override;

    std::string getName() const override;
};
#ifndef PROJECT_SWA_JUMPCOMPONENT_H
#define PROJECT_SWA_JUMPCOMPONENT_H

#include "Component.h"

class JumpComponent : public Component {
private:
    double _jumpAcceleration;
public:
    JumpComponent();

    explicit JumpComponent(double acceleration);
    double getAcceleration() const;
    void setAcceleration(double acceleration);
    ~JumpComponent() override;

    void accept(SerializationVisitor &visitor) override;

    std::string getName() const override;
};

#endif //PROJECT_SWA_JUMPCOMPONENT_H

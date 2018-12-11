#include "../../../Headers/GameECS/Components/JumpComponent.h"

JumpComponent::JumpComponent() : JumpComponent(400){

}

JumpComponent::JumpComponent(double acceleration) : _jumpAcceleration(acceleration) {

}

double JumpComponent::getAcceleration() const {
    return _jumpAcceleration;
}

void JumpComponent::setAcceleration(double acceleration) {
    _jumpAcceleration = acceleration;
}

void JumpComponent::accept(SerializationVisitor &visitor) {
    visitor.visit("jumpAcceleratation", _jumpAcceleration);
}

std::string JumpComponent::getName() const {
    return "JumpComponent";
}

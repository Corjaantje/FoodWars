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

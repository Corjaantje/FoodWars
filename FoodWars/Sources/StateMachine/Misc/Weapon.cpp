#include <utility>

#include "../../../Headers/StateMachine/Misc/Weapon.h"

Weapon::Weapon() : Weapon("", 0) {

}

Weapon::Weapon(const std::string &imageUrl, int ammo) : _imageUrl(imageUrl), _ammo(ammo) {

}

int Weapon::getAmmo() const {
    return _ammo;
}

std::string Weapon::getImage() const {
    return _imageUrl;
}

void Weapon::lowerAmmo() {
    _ammo--;
}

void Weapon::accept(SerializationVisitor &visitor) {
    visitor.visit("ammo", _ammo);
    visitor.visit("image", _imageUrl);
}
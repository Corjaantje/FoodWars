#include <utility>

#include "../../../Headers/StateMachine/Misc/Weapon.h"

Weapon::Weapon() : Weapon("", 0) {

}

Weapon::Weapon(const std::string &imageUrl, int ammo, Faction faction) : _imageUrl(std::move(imageUrl)), _ammo(ammo), _entityManager(), _faction{faction} {

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

void Weapon::setAmmo(int val) {
    _ammo = val;
}

const Faction Weapon::getFaction() const {
    return _faction;
}

void Weapon::accept(SerializationVisitor &visitor) {
    visitor.visit("ammo", _ammo);
    visitor.visit("image", _imageUrl);
}

std::string Weapon::getName() const {
    return "Weapon";
}

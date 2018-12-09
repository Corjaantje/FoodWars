#include <utility>

#include "../../../Headers/StateMachine/Misc/Weapon.h"

Weapon::Weapon(std::string imageUrl, int ammo) : _imageUrl(std::move(imageUrl)), _ammo(ammo), _entityManager() {

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

#include <utility>

#include "../../../Headers/GameECS/Components/PlayerComponent.h"

PlayerComponent::PlayerComponent() : PlayerComponent(0, Faction::WHITE) {

}

PlayerComponent::PlayerComponent(int id, Faction faction) : _playerID(id), _score(0), _selectedWeaponAvailability(5), _faction(faction) {
    createWeapon<Weapon>("carrot.png", 5);
    createWeapon<Weapon>("ham.png", 5);
    createWeapon<Weapon>("candycane.png", 5);

    _selectedWeapon = _weapons[0];
}

void PlayerComponent::setSelectedWeapon(std::string selectionType) {
    if (selectionType == "next") {
        for (int i = 0; i < _weapons.size(); i++) {
            if (_selectedWeapon == _weapons[i]) {
                if ((i + 1) < _weapons.size()) {
                    _selectedWeapon = _weapons[i + 1];
                } else {
                    _selectedWeapon = _weapons[0];
                }
                break;
            }
        }
    }
    else if (selectionType == "previous") {
        for (int i = 0; i < _weapons.size(); i++) {
            if (_selectedWeapon == _weapons[i]) {
                if ((i - 1) >= 0) {
                    _selectedWeapon = _weapons[i - 1];
                } else {
                    _selectedWeapon = _weapons[_weapons.size() - 1];
                }
                break;
            }
        }
    }
}

void PlayerComponent::setPlayerID(int id) {
    _playerID = id;
}

void PlayerComponent::addScore(int score) {
    _score += score;
}

int PlayerComponent::getPlayerID() const {
    return _playerID;
}

int PlayerComponent::getScore() const {
 return _score;
}

Weapon* PlayerComponent::getSelectedWeapon() const {
    return _selectedWeapon;
}

void PlayerComponent::setSelectedWeaponAvailability(int weaponAvail) {
    _selectedWeaponAvailability = weaponAvail;
}

int PlayerComponent::getSelectedWeaponAvailability() const {
    return _selectedWeapon->getAmmo();
}

void PlayerComponent::setFaction(Faction faction) {
    _faction = faction;
}

Faction PlayerComponent::getFaction() const {
    return _faction;
}
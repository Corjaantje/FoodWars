#include <utility>

#include "../../../Headers/GameECS/Components/PlayerComponent.h"

PlayerComponent::PlayerComponent() : PlayerComponent(0) {

}

PlayerComponent::PlayerComponent(int id) : _playerID(id), _score(0), _selectedWeaponIndex(-1) {
    createWeapon<Weapon>("carrot.png", 5);
    createWeapon<Weapon>("ham.png", 5);
    createWeapon<Weapon>("candycane.png", 5);
    _selectedWeaponIndex = 0;
}

void PlayerComponent::setSelectedWeapon(const std::string &selectionType) {
    if (selectionType == "next") {
        _selectedWeaponIndex += 1;
        if (_selectedWeaponIndex >= _weapons.size())
            _selectedWeaponIndex = 0;
    } else if (selectionType == "previous") {
        _selectedWeaponIndex -= 1;
        if (_selectedWeaponIndex < 0)
            _selectedWeaponIndex = _weapons.size() - 1;
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
    return _weapons.size() < _selectedWeaponIndex && _selectedWeaponIndex >= 0 ? _weapons[_selectedWeaponIndex].get()
                                                                               : nullptr;
}

int PlayerComponent::getSelectedWeaponAvailability() const {
    return getSelectedWeapon() ? getSelectedWeapon()->getAmmo() : -1;
}

void PlayerComponent::accept(SerializationVisitor &visitor) {
    visitor.visit("playerId", _playerID);
    for (const auto &weapon : _weapons) {
        visitor.visit("weapon", *weapon);
    }
    visitor.visit("selectedWeaponIndex", _selectedWeaponIndex);
    visitor.visit("score", _score);
}

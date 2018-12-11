#include <utility>
#include <algorithm>
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
    std::vector<SerializationReceiver *> weapons;
    std::transform(_weapons.begin(), _weapons.end(), std::back_inserter(weapons),
                   [](std::unique_ptr<Weapon> &weaponPtr) {
                       return weaponPtr.get();
                   });
    visitor.visit("weapons", weapons);
    visitor.visit("selectedWeaponIndex", _selectedWeaponIndex);
    visitor.visit("score", _score);
}

void PlayerComponent::accept(DeserializationVisitor &visitor) {
    visitor.visit("playerId", _playerID);
    std::vector<SerializationReceiver *> weapons;
    visitor.visit("weapons", weapons, [weapons = &_weapons]() {
        weapons->push_back(std::make_unique<Weapon>());
        return static_cast<SerializationReceiver *>(weapons->back().get());
    });
    visitor.visit("selectedWeaponIndex", _selectedWeaponIndex);
    visitor.visit("score", _score);
}

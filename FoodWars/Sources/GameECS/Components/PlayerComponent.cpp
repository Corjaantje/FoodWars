#include <utility>
#include <algorithm>
#include <numeric>
#include "../../../Headers/GameECS/Components/PlayerComponent.h"

PlayerComponent::PlayerComponent() : PlayerComponent(0, Faction::WHITE) {

}

PlayerComponent::PlayerComponent(int id, Faction faction) : _playerID(id), _score(0), _selectedWeaponAvailability(5), _faction(faction), _isAlive{true} {
    switch (faction) {
        case Faction::YELLOW:
            initWeapon(0,0,3);
            _selectedWeaponIndex = 2;
            break;
        case Faction::RED:
            initWeapon(0,3,0);
            _selectedWeaponIndex = 1;
            break;
        case Faction::GREEN:
            initWeapon(3,0,0);
            _selectedWeaponIndex = 0;
            break;
        default:
            _selectedWeaponIndex = 0;
            initWeapon(1,1,1);
            break;
    }
}

void PlayerComponent::initWeapon(int ammo, int ammo1, int ammo2) {
    createWeapon<Weapon>("carrot.png", ammo, Faction::GREEN, 20);
    createWeapon<Weapon>("ham.png", ammo1, Faction::RED, 20);
    createWeapon<Weapon>("candycane.png", ammo2, Faction::YELLOW, 20);
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
    return _weapons.size() > _selectedWeaponIndex && _selectedWeaponIndex >= 0 ? _weapons[_selectedWeaponIndex].get()
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

void PlayerComponent::setFaction(Faction faction) {
    _faction = faction;
}

Faction PlayerComponent::getFaction() const {
    return _faction;
}

void PlayerComponent::setIsAlive(bool alive) {
    _isAlive = alive;
}

bool PlayerComponent::isAlive() const {
    return _isAlive;
}

void PlayerComponent::addToWeaponType(const std::string &weaponType, int increaseBy) {
    auto weaponIterator = std::find_if(_weapons.begin(), _weapons.end(), [&weaponType](const std::unique_ptr<Weapon>& obj) {
        return obj->getImage() == weaponType+".png";
    });

    if (weaponIterator != _weapons.end()){
        weaponIterator[0]->setAmmo(weaponIterator[0]->getAmmo()+increaseBy);
    } else {
        // Future expansion possibility: adding weapons which players don't spawn with. Would require faction info.
    }


}

int PlayerComponent::getAmountOFWeapons() const{
    return _weapons.size();
}

void PlayerComponent::accept(DeserializationVisitor &visitor) {
    visitor.visit("playerId", _playerID);
    std::vector<SerializationReceiver *> weapons;
    visitor.visit("weapons", weapons, [weapons = &_weapons]() {
        weapons->push_back(std::make_unique<Weapon>());
        return static_cast<SerializationReceiver *>(weapons->back().get());
    }); //warning!: not sure if this works
    visitor.visit("selectedWeaponIndex", _selectedWeaponIndex);
    visitor.visit("score", _score);
}

std::string PlayerComponent::getName() const {
    return "PlayerComponent";
}

int PlayerComponent::getTotalAmmoCount() const {
    return std::accumulate(_weapons.begin(), _weapons.end(), 0, [](int sum, const std::unique_ptr<Weapon> &weapon) {
        return sum += weapon->getAmmo();
    });;
}

#include <utility>

#include "../../../Headers/GameECS/Components/PlayerComponent.h"

PlayerComponent::PlayerComponent(int id) : _playerID(id), _score(0), _selectedWeapon("carrot.png"), _selectedWeaponAvailability(5) {

}

void PlayerComponent::setSelectedWeapon(std::string ImageURL) {
    _selectedWeapon = std::move(ImageURL);
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

std::string PlayerComponent::getSelectedWeapon() const{
    return _selectedWeapon;
}

void PlayerComponent::setSelectedWeaponAvailability(int weaponAvail) {
    _selectedWeaponAvailability = weaponAvail;
}

int PlayerComponent::getSelectedWeaponAvailability() const{
    return _selectedWeaponAvailability;
}
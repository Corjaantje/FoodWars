#ifndef PROJECT_SWA_PLAYERCOMPONENT_H
#define PROJECT_SWA_PLAYERCOMPONENT_H

#include <vector>
#include <string>
#include "Component.h"
#include "../../../Headers/StateMachine/Misc/Weapon.h"

class PlayerComponent : public Component {
public:
    PlayerComponent();
    explicit PlayerComponent(int id);
public:
    void setPlayerID(int id);
    void setSelectedWeapon(std::string selectionType);
    void setSelectedWeaponAvailability(int weaponAvail);
    void addScore(int score);

    int getPlayerID() const;
    int getScore() const;
    Weapon* getSelectedWeapon() const;
    int getSelectedWeaponAvailability() const;

private:
    int _playerID;
    int _score;
    int _selectedWeaponAvailability;
    std::vector<Weapon*> _weapons{};
    Weapon* _selectedWeapon;

    template<typename T, typename... Args>
    Weapon *createWeapon(Args &&... args) {
        T *weapon = new T(std::forward<Args>(args)...);
        _weapons.push_back(weapon);
        return weapon;
    }
};


#endif //PROJECT_SWA_PLAYERCOMPONENT_H

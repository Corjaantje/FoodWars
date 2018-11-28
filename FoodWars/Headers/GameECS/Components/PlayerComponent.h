#ifndef PROJECT_SWA_PLAYERCOMPONENT_H
#define PROJECT_SWA_PLAYERCOMPONENT_H


#include <vector>
#include <string>
#include "Component.h"

class PlayerComponent : public Component {
public:
    PlayerComponent() = default;
    explicit PlayerComponent(int id);
public:
    void setPlayerID(int id);
    void setSelectedWeapon(std::string ImageURL);
    void setSelectedWeaponAvailability(int weaponAvail);
    void addScore(int score);

    int getPlayerID() const;
    int getScore() const;
    std::string getSelectedWeapon();
    int getSelectedWeaponAvailability();

private:
    int _playerID;
    int _score;
    std::string _selectedWeapon;
    int _selectedWeaponAvailability;
};


#endif //PROJECT_SWA_PLAYERCOMPONENT_H

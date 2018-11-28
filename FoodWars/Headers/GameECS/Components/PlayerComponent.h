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
    void addScore(int score);

    int getPlayerID() const;
    int getScore() const;
private:
    int _playerID;
    int _score;
    std::string _selectedWeapon;
};


#endif //PROJECT_SWA_PLAYERCOMPONENT_H

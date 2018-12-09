#ifndef PROJECT_SWA_PLAYERCOMPONENT_H
#define PROJECT_SWA_PLAYERCOMPONENT_H

#include <memory>
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

    void setSelectedWeapon(const std::string &selectionType);
    void addScore(int score);

    int getPlayerID() const;
    int getScore() const;
    Weapon* getSelectedWeapon() const;
    int getSelectedWeaponAvailability() const;

    void accept(SerializationVisitor &visitor) override;

    void accept(DeserializationVisitor &visitor) override;

private:
    int _playerID;
    int _score;
    int _selectedWeaponIndex;
    std::vector<std::unique_ptr<Weapon>> _weapons{};

    template<typename T, typename... Args>
    Weapon *createWeapon(Args &&... args) {
        std::unique_ptr<T> weapon = std::make_unique<T>(std::forward<Args>(args)...);
        _weapons.push_back(std::move(weapon));
        return weapon.get();
    }
};


#endif //PROJECT_SWA_PLAYERCOMPONENT_H

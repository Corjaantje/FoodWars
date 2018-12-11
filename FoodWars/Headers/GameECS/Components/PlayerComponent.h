#ifndef PROJECT_SWA_PLAYERCOMPONENT_H
#define PROJECT_SWA_PLAYERCOMPONENT_H

#include <memory>
#include <vector>
#include <string>
#include "Component.h"
#include "../../../Headers/StateMachine/Misc/Weapon.h"
#include "../../StateMachine/Misc/FactionEnum.h"

class PlayerComponent : public Component {
public:
    PlayerComponent();
    explicit PlayerComponent(int id, Faction faction);
public:
    void setPlayerID(int id);
    void setSelectedWeapon(std::string selectionType);
    void setSelectedWeaponAvailability(int weaponAvail);
    void addScore(int score);
    void setFaction(Faction faction);
    void setIsAlive(bool alive);

    int getPlayerID() const;
    int getScore() const;
    Weapon* getSelectedWeapon() const;
    int getSelectedWeaponAvailability() const;
    const Faction getFaction() const;
    bool getIsAlive() const;

    void accept(SerializationVisitor &visitor) override;

    void accept(DeserializationVisitor &visitor) override;

    std::string getName() const override;

private:
    int _playerID;
    int _score;
    int _selectedWeaponAvailability;
    int _selectedWeaponIndex;
    bool _isAlive; //todo: why?
    std::vector<std::unique_ptr<Weapon>> _weapons{};
    Faction _faction;

    template<typename T, typename... Args>
    Weapon *createWeapon(Args &&... args) {
        std::unique_ptr<T> weapon = std::make_unique<T>(std::forward<Args>(args)...);
        _weapons.push_back(std::move(weapon));
        return weapon.get();
    }
};


#endif //PROJECT_SWA_PLAYERCOMPONENT_H

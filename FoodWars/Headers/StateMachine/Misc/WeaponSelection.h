#ifndef PROJECT_SWA_WEAPONSELECTION_H
#define PROJECT_SWA_WEAPONSELECTION_H

#include "../../../Headers/GameECS/Components/PlayerComponent.h"
#include "../../GameECS/Entities/EntityManager.h"


class WeaponSelection {
public:
    WeaponSelection(EntityManager &entityManager);
    ~WeaponSelection() = default;
private:
    EntityManager* _entityManager;
public:
    void newSelectedWeapon(int playerId, std::string selection);
};


#endif //PROJECT_SWA_WEAPONSELECTION_H

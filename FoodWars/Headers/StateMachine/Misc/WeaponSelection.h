#ifndef PROJECT_SWA_WEAPONSELECTION_H
#define PROJECT_SWA_WEAPONSELECTION_H

#include "../../../Headers/GameECS/Components/PlayerComponent.h"
#include "../../GameECS/Entities/EntityManager.h"

class WeaponSelection {
public:
    WeaponSelection();
    ~WeaponSelection();
private:
    EntityManager* _entityManager;
};

#endif //PROJECT_SWA_WEAPONSELECTION_H

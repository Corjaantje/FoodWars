#ifndef PROJECT_SWA_POWERUPMANAGER_H
#define PROJECT_SWA_POWERUPMANAGER_H

#include <cstdlib>
#include "../Headers/GameECS/Entities/EntityManager.h"

class PowerupManager {
private:

public:
    PowerupManager() = default;
    ~PowerupManager() = default;

    void spawnPowerups(EntityManager *entityManager);
};

#endif //PROJECT_SWA_POWERUPMANAGER_H

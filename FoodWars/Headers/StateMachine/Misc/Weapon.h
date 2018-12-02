#ifndef PROJECT_SWA_WEAPON_H
#define PROJECT_SWA_WEAPON_H

#include <string>
#include "../../GameECS/Entities/EntityManager.h"


class Weapon {
public:
    Weapon(std::string imageUrl, int ammo);
    ~Weapon() = default;
public:
    void setAmmo();

    int getAmmo() const;
    std::string getImage() const;
private:
    EntityManager _entityManager;
    std::string _imageUrl;
    int _ammo;
};

#endif //PROJECT_SWA_WEAPON_H

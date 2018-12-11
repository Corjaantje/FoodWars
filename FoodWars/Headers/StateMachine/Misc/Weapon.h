#ifndef PROJECT_SWA_WEAPON_H
#define PROJECT_SWA_WEAPON_H

#include <string>
#include "../../GameECS/Entities/EntityManager.h"
#include "FactionEnum.h"


class Weapon {
public:
    Weapon(std::string imageUrl, int ammo, Faction faction);
    ~Weapon() = default;
public:
    void lowerAmmo();
    void setAmmo(int val);
    int getAmmo() const;
    std::string getImage() const;
    const Faction getFaction() const;
private:
    EntityManager _entityManager;
    std::string _imageUrl;
    int _ammo;
    const Faction _faction;
};

#endif //PROJECT_SWA_WEAPON_H

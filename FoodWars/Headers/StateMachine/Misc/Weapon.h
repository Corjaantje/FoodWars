#ifndef PROJECT_SWA_WEAPON_H
#define PROJECT_SWA_WEAPON_H

#include <string>
#include "../../../../TonicEngine/Headers/Storage/SerializationReceiver.h"
#include "FactionEnum.h"

class Weapon : public SerializationReceiver {
public:
    Weapon();
    Weapon(const std::string &imageUrl, int ammo, Faction faction);
    ~Weapon() = default;
public:
    void lowerAmmo();
    void setAmmo(int val);
    int getAmmo() const;
    std::string getImage() const;

    void accept(SerializationVisitor &visitor) override;

    std::string getName() const override;

    Faction getFaction() const;
private:
    std::string _imageUrl;
    int _ammo;
    const Faction _faction;
};

#endif //PROJECT_SWA_WEAPON_H

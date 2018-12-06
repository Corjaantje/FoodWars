#ifndef PROJECT_SWA_WEAPON_H
#define PROJECT_SWA_WEAPON_H

#include <string>
#include "../../../../TonicEngine/Headers/Storage/SerializationReceiver.h"

class Weapon : public SerializationReceiver {
public:
    Weapon(const std::string &imageUrl, int ammo);
    ~Weapon() = default;
public:
    void lowerAmmo();

    int getAmmo() const;
    std::string getImage() const;

    void accept(SerializationVisitor &visitor) override;

private:
    std::string _imageUrl;
    int _ammo;
};

#endif //PROJECT_SWA_WEAPON_H

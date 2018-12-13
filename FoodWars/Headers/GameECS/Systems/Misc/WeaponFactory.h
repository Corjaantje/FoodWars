#ifndef PROJECT_SWA_WEAPONFACTORY_H
#define PROJECT_SWA_WEAPONFACTORY_H


#include "../../Components/ItemComponent.h"

class WeaponFactory {
public:
    WeaponFactory();
    ~WeaponFactory();
    int getMapSize() const;
    ItemComponent createItem(const std::string& weapon);
private:
    std::unordered_map<std::string, ItemComponent> _weaponMap;
};


#endif //PROJECT_SWA_WEAPONFACTORY_H

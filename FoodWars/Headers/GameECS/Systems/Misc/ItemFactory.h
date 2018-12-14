//
// Created by bryanvanlierop on 12/12/2018.
//

#ifndef PROJECT_SWA_ITEMFACTORY_H
#define PROJECT_SWA_ITEMFACTORY_H

#include <unordered_map>
#include "../../Components/ItemComponent.h"

class ItemFactory {
public:
    ItemFactory();
    ~ItemFactory();
    int getMapSize() const;
    ItemComponent createItem(const std::string& item);
private:
    std::unordered_map<std::string, ItemComponent> _itemMap;
    ItemComponent createWeapon(const std::string &weaponName);
    ItemComponent createWeapon(const std::string &weaponName, int ammoCount);
};
#endif //PROJECT_SWA_ITEMFACTORY_H

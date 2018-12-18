//
// Created by bryanvanlierop on 12/12/2018.
//

#include "../../../../Headers/GameECS/Systems/Misc/ItemFactory.h"
#include "../../../../Headers/GameECS/Components/DamageableComponent.h"
#include "../../../../Headers/GameECS/Components/TurnComponent.h"
#include "../../../../Headers/GameECS/Components/PlayerComponent.h"

ItemFactory::ItemFactory() {
    _itemMap =
    {{
        {"PowerupPill", ItemComponent{[](EntityManager& e, const CollisionEvent& event)
        {
          e.getComponentFromEntity<DamageableComponent>(event.getEntity())->increaseHealth(50);
        }}},
        {"PowerupCoffee", ItemComponent{[](EntityManager& e, const CollisionEvent& event)
        {
          e.getComponentFromEntity<TurnComponent>(event.getEntity())->setEnergy(100);
        }}},
        {"carrot", createWeapon("carrot")},
        {"ham", createWeapon("ham")},
        {"candycane", createWeapon("candycane")}
    }};
}

ItemFactory::~ItemFactory() = default;
ItemComponent ItemFactory::createItem(const std::string& item) {
    return _itemMap.at(item);
}

int ItemFactory::getMapSize() const {
    return _itemMap.size();
}

ItemComponent ItemFactory::createWeapon(const std::string &weaponName, int ammoCount) {
    return ItemComponent{[weaponName = weaponName, ammoCount = ammoCount](EntityManager& e, const CollisionEvent& event)
                         {
                             e.getComponentFromEntity<PlayerComponent>(event.getEntity())->addToWeaponType(weaponName, ammoCount);
                         }};
}

ItemComponent ItemFactory::createWeapon(const std::string &weaponName) {
    return createWeapon(weaponName, 1);
}

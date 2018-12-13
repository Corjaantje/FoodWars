#include "../../../../Headers/GameECS/Systems/Misc/WeaponFactory.h"
#include "../../../../Headers/GameECS/Components/PlayerComponent.h"

WeaponFactory::WeaponFactory() {
    _weaponMap =
    {
         {"carrot", ItemComponent{"carrot", [](EntityManager& e, const CollisionEvent& event) //Possible future change: more than 1
         {
             e.getComponentFromEntity<PlayerComponent>(event.getEntity())->addToWeaponType("carrot", 1);
         }}},
         {"ham", ItemComponent{"ham", [](EntityManager& e, const CollisionEvent& event)
         {
             e.getComponentFromEntity<PlayerComponent>(event.getEntity())->addToWeaponType("ham", 1);
         }}},
         {"candycane", ItemComponent{"candycane", [](EntityManager& e, const CollisionEvent& event)
         {
             e.getComponentFromEntity<PlayerComponent>(event.getEntity())->addToWeaponType("candycane", 1);
         }}}
     };
}

WeaponFactory::~WeaponFactory() = default;

int WeaponFactory::getMapSize() const {
    return _weaponMap.size();
}

ItemComponent WeaponFactory::createItem(const std::string &weapon) {
    return _weaponMap.at(weapon);
}

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
        {"cake", ItemComponent{"cake", [](EntityManager& e, const CollisionEvent& event)
        {
          e.getComponentFromEntity<DamageableComponent>(event.getEntity())->increaseHealth(50);
        }}},
        {"painkiller", ItemComponent{"painkiller", [](EntityManager& e, const CollisionEvent& event)
        {
          e.getComponentFromEntity<TurnComponent>(event.getEntity())->setEnergy(100);
        }}},
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
    }};
}

ItemFactory::~ItemFactory() = default;
ItemComponent ItemFactory::createItem(const std::string& item) {
    return _itemMap.at(item);
}

int ItemFactory::getMapSize() const {
    return _itemMap.size();
}

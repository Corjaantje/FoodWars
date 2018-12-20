#include "../../../Headers/GameECS/Systems/PowerupSystem.h"
#include "../../../Headers/GameECS/Components/DrawableComponent.h"
#include "../../../Headers/GameECS/Components/Collider/BoxCollider.h"
#include "../../../Headers/GameECS/Components/PositionComponent.h"
#include "../../../Headers/GameECS/Components/GravityComponent.h"
#include "../../../../TonicEngine/Headers/Visual/Shapes/ShapeSprite.h"
#include "../../../Headers/GameECS/Components/PlayerComponent.h"
#include "../../../Headers/GameECS/Components/DamageableComponent.h"
#include "../../../Headers/GameECS/Components/AnimationComponent.h"
#include "../../../../TonicEngine/Headers/Visual/Shapes/ShapeRectangle.h"
#include "../../../../TonicEngine/Headers/Storage/FileManager.h"

PowerupSystem::PowerupSystem(IObservable<CollisionEvent> &collisionEventObservable,
                             IObservable<TurnSwitchedEvent> &turnSwitchedEventObservable, EntityManager &entityManager)
        : CollisionEventHandler(collisionEventObservable), TurnSwitchedEventHandler(turnSwitchedEventObservable),
          _entityManager{&entityManager}, _itemFactory{ItemFactory{}}, _random{Random{}} {
    _itemMap[0] = "PowerupCoffee";
    _itemMap[1] = "PowerupPill";
    _weaponMap[0] = "carrot";
    _weaponMap[1] = "ham";
    _weaponMap[2] = "candycane";
}

void PowerupSystem::spawnDrop(const std::unordered_map<int, std::string> &dropMap) {

    int dropX = _random.between(0, 1571);
    int dropY = 0;
    int dropWidth = 40;
    int dropHeight = 40;

    int dropID = _entityManager->createEntity();
    int dropChance = _random.between(0, dropMap.size() - 1);

    const std::string &name = dropMap.at(dropChance);
    auto weaponType = _itemFactory.createItem(name);
    _entityManager->addComponentToEntity(dropID, std::make_unique<ItemComponent>(weaponType));
    _entityManager->addComponentToEntity<DrawableComponent>(dropID,
                                                            std::make_unique<ShapeSprite>(dropWidth, dropHeight, dropX,
                                                                                          dropY,
                                                                                          name + ".png", 3));

    typedef std::unordered_map<int, std::string>::value_type map_value_type;
    if (_itemMap.end() ==
        find_if(_itemMap.begin(), _itemMap.end(), [&name](const map_value_type &vt) { return vt.second == name; })) {
        const int amountOfSprites = 6;
        std::vector<std::unique_ptr<IShape>> animationShapes{amountOfSprites};
        for (int i = 1; i < amountOfSprites; i++) {
            auto sprite = name + "0" + std::to_string(i) + ".png";
            animationShapes[i] = std::make_unique<ShapeSprite>(dropWidth, dropHeight, dropX, dropY, sprite, 3);
        }
        _entityManager->addComponentToEntity<AnimationComponent>(dropID, std::move(animationShapes), 0.1);
    }
    _entityManager->addComponentToEntity<BoxCollider>(dropID, dropWidth, dropHeight, true);
    _entityManager->addComponentToEntity<PositionComponent>(dropID, dropX, dropY);
    _entityManager->addComponentToEntity<GravityComponent>(dropID, 5);
}

bool PowerupSystem::canHandle(const CollisionEvent &collisionEvent) {
    int player = collisionEvent.getEntity();
    int item = collisionEvent.getOtherEntity();
    return _entityManager->getComponentFromEntity<PlayerComponent>(player) &&
           _entityManager->getComponentFromEntity<ItemComponent>(item);
}

void PowerupSystem::handleCollisionEvent(const CollisionEvent &collisionEvent) {
    int item = collisionEvent.getOtherEntity();
    auto itemComponent = _entityManager->getComponentFromEntity<ItemComponent>(item);
    if (!itemComponent) {
        item = collisionEvent.getEntity();
        itemComponent = _entityManager->getComponentFromEntity<ItemComponent>(item);
    }
    itemComponent->getLamda()(*_entityManager, collisionEvent);
    _entityManager->addComponentToEntity<DamageableComponent>(item);
    _entityManager->getComponentFromEntity<DamageableComponent>(item)->destroy();
}

void PowerupSystem::update(double deltaTime) {

}

void PowerupSystem::handleTurnSwitchedEvent(const TurnSwitchedEvent &turnSwitchedEvent) {
    Random random;
    if (random.between(0, 1) == 0) { spawnDrop(_itemMap); }
    spawnDrop(_weaponMap);
}



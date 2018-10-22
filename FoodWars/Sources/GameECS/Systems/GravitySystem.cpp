#include <utility>
#include "../../../Headers/GameECS/Systems/GravitySystem.h"
#include "../../../Headers/GameECS/Components/GravityComponent.h"
#include "../../../Headers/GameECS/Components/MoveComponent.h"
#include "../../../Headers/GameECS/Components/DrawableComponent.h"

GravitySystem::~GravitySystem() = default;

GravitySystem::GravitySystem(std::shared_ptr<EntityManager> entityManager) : _entityManager(std::move(entityManager)) {

}

void GravitySystem::update(double dt) {
    for(auto const &iterator: _entityManager->getAllEntitiesWithComponent<GravityComponent>()) {
        if(_entityManager->getComponentFromEntity<DrawableComponent>(iterator.first)->shape->yPos < 250) {
            _entityManager->addComponentToEntity(iterator.first, new MoveComponent(PositionComponent(0, 1),
                                                                                   iterator.second->gravityApplied));
        }
    }
}
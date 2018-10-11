#include <iostream>
#include "../../../Headers/GameECS/Systems/DrawSystem.h"
#include "../../../Headers/GameECS/Systems/IBaseSystem.h"
#include "../../../Headers/GameECS/Components/DrawableComponent.h"

DrawSystem::DrawSystem(EntityManager *entityManager){
    _entityManager = entityManager;
}

DrawSystem::~DrawSystem() {

}
void DrawSystem::update(double dt) {
    DrawableComponent drawableComponent;
    DrawableComponent _componentList[1] = {drawableComponent};
    _entityManager->createEntity(_componentList, 1);
    _entityManager->createEntity(_componentList, 1);
    _entityManager->createEntity(_componentList, 1);

    _entityManager->getAllEntities<DrawableComponent>();
    //cout << map.size();
}
#include <iostream>
#include "../../../Headers/GameECS/Systems/DrawSystem.h"
#include "../../../Headers/GameECS/Systems/IBaseSystem.h"
#include "../../../Headers/GameECS/Components/DrawableComponent.h"

DrawSystem::DrawSystem(std::shared_ptr<EntityManager> entityManager, std::shared_ptr<VisualFacade> visualFacade){
    _entityManager = entityManager;
    _visualFacade = visualFacade;
    DrawableComponent worldBlock;
    int id = _entityManager->createEntity();
    _entityManager->addComponentToEntity(id, &worldBlock);
    _renderList.rectangleList.emplace_back(ShapeRectangle{200, 200, 200, 200, Colour { 255, 255, 0, 100}});
}

DrawSystem::~DrawSystem() {

}

void DrawSystem::update(double dt) {
    std::map<int, std::shared_ptr<DrawableComponent>> drawComps = _entityManager->getAllEntitiesWithComponent<DrawableComponent>();

    for(int i=0; i< drawComps.size(); i++){
        //_renderList.rectangleList.emplace();
    }
    _visualFacade->render(_renderList);
}
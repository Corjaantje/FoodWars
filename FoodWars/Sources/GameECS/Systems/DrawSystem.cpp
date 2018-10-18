#include <iostream>
#include "../../../Headers/GameECS/Systems/DrawSystem.h"
#include "../../../Headers/GameECS/Systems/IBaseSystem.h"
#include "../../../Headers/GameECS/Components/DrawableComponent.h"

DrawSystem::DrawSystem(std::shared_ptr<EntityManager> entityManager, std::shared_ptr<VisualFacade> visualFacade){
    _entityManager = entityManager;
    _visualFacade = visualFacade;
    std::cout << "Entity manager: " << entityManager << std::endl;
    for(int i=0; i< 50; i++) {
        int id = _entityManager->createEntity();
        DrawableComponent *comp = new DrawableComponent();
        _entityManager->addComponentToEntity(id, comp);
        comp->shape = std::make_unique<ShapeRectangle>(ShapeRectangle({i*5, i, i, i, Colour{i*5, 0, 255, 100}}));
    }
}

DrawSystem::~DrawSystem() {

}

void DrawSystem::update(double dt) {
    std::map<int, std::shared_ptr<DrawableComponent>> drawComps = _entityManager->getAllEntitiesWithComponent<DrawableComponent>();
    _renderList.rectangleList.clear();
    _renderList.spriteList.clear();
    for(int i=0; i < drawComps.size(); i++){
        drawComps[i]->shape->addToRender(&_renderList);
    }
    _visualFacade->render(_renderList);
}
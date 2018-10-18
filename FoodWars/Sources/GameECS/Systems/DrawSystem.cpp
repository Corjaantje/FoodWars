#include <iostream>
#include "../../../Headers/GameECS/Systems/DrawSystem.h"
#include "../../../Headers/GameECS/Systems/IBaseSystem.h"
#include "../../../Headers/GameECS/Components/DrawableComponent.h"

DrawSystem::DrawSystem(std::shared_ptr<EntityManager> entityManager, std::shared_ptr<VisualFacade> visualFacade){
    _entityManager = entityManager;
    _visualFacade = visualFacade;
    std::cout << "Entity manager: " << entityManager << std::endl;
    DrawSystem::generateTerrain();
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

void DrawSystem::generateTerrain() {
    for(int y=288; y < 480; y+=32){
        for(int x=0; x < 640; x+=32) {
            int randomNum = rand() % 19 + (-9);
            int randomNum2 = rand() % 19 + (-9);
            int randomNum3 = rand() % 19 + (-9);
            int id = _entityManager->createEntity();
            DrawableComponent *comp = new DrawableComponent();
            _entityManager->addComponentToEntity(id, comp);
            comp->shape = std::make_unique<ShapeRectangle>(ShapeRectangle({32, 32, x, y, Colour{149 + randomNum, 69 + randomNum2, 53 + randomNum3, 100}}));
        }
    }
}
#include <iostream>
#include <sstream>
#include "../../../Headers/GameECS/Systems/DrawSystem.h"
#include "../../../Headers/GameECS/Systems/IBaseSystem.h"
#include "../../../Headers/GameECS/Components/DrawableComponent.h"
#include "../../../Headers/GameECS/Components/Collider/BoxCollider.h"
#include "../../../Headers/GameECS/Components/TurnComponent.h"

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
    _renderList.textList.clear();
    std::string str = std::to_string(1/dt).substr(0, 2) + " FPS";
    _renderList.textList.emplace_back(ShapeText(0, 0, str, 80, 75, 50, Colour(0, 0, 0, 0)));
    for(int i=0; i < drawComps.size(); i++){
        drawComps[i]->shape->addToRender(&_renderList);
    }
    for(const auto &iterator: _entityManager->getAllEntitiesWithComponent<TurnComponent>()) {
        if(iterator.second->isMyTurn()){
            ShapeText timerText {500, 0, std::to_string(iterator.second->getRemainingTime()).substr(0, 4) + " sec.", 100, 75, 50, Colour{0, 0, 0, 0}};
            timerText.addToRender(&_renderList);
            break;
        }
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
            _entityManager->addComponentToEntity(id, new BoxCollider(32, 32));
            comp->shape = std::make_unique<ShapeRectangle>(ShapeRectangle({32, 32, x, y, Colour{149 + randomNum, 69 + randomNum2, 53 + randomNum3, 100}}));
        }
    }
}
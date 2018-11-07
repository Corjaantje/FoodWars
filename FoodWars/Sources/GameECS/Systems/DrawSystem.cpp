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
}

DrawSystem::~DrawSystem() {

}

void DrawSystem::update(double dt) {
    std::map<int, std::shared_ptr<DrawableComponent>> drawComps = _entityManager->getAllEntitiesWithComponent<DrawableComponent>();
    _renderList.rectangleList.clear();
    _renderList.spriteList.clear();
    _renderList.textList.clear();
    _updateCallCount++;
    _deltaTimeTotal += dt;
    if(_updateCallCount >= 10){
        _fpsString = std::to_string((10/_deltaTimeTotal)).substr(0, 2) + " FPS";
        _updateCallCount = 0;
        _deltaTimeTotal = 0;
    }
    _renderList.textList.emplace_back(ShapeText(0, 0, _fpsString, 80, 75, 50, Colour(0, 0, 0, 0)));
    _renderList.rectangleList.emplace_back(ShapeRectangle(640,480,0,0, Colour(173,216,230,0)));
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


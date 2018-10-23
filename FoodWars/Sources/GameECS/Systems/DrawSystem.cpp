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

void DrawSystem::generateTerrain() {
    for(int y=112; y < 480; y+=16) {
        for (int x=0; x < 640; x+=16) {
            if (y >= 160 && x >= 528 && x <= 592) {
                generateTerrainDrawables(x, y);
            } else if ((y >= 176 && x >= 496)) {
                generateTerrainDrawables(x, y);
            } else if (y >= 176 && x > 560) {
                generateTerrainDrawables(x, y);
            } else if (y >= 192 && x >= 464) {
                generateTerrainDrawables(x, y);
            } else if (y >= 208 && x >= 432) {
                generateTerrainDrawables(x, y);
            } else if (y >= 224 && x >= 400) {
                generateTerrainDrawables(x, y);
            } else if (y >= 240 && x >= 368) {
                generateTerrainDrawables(x, y);
            } else if (y >= 256 && x >= 336) {
                generateTerrainDrawables(x, y);
            } else if (y >= 192 && x >= 0 && x <= 64 ) {
                generateTerrainDrawables(x, y);
            } else if (y >= 208 && x >= 0 && x <= 96 ) {
                generateTerrainDrawables(x, y);
            } else if (y >= 224 && x >= 0 && x <= 112 ) {
                generateTerrainDrawables(x, y);
            } else if (y >= 256 && x >= 0 && x <= 128 ) {
                generateTerrainDrawables(x, y);
            } else if (y >= 288 ) {
                generateTerrainDrawables(x, y);
            }
        }
    }
}

void DrawSystem::generateTerrainDrawables(int x, int y) {
    int randomNum = rand() % 19 + (-9);
    int randomNum2 = rand() % 19 + (-9);
    int randomNum3 = rand() % 19 + (-9);
    int id = _entityManager->createEntity();
    DrawableComponent *comp = new DrawableComponent();
    _entityManager->addComponentToEntity(id, comp);
    _entityManager->addComponentToEntity(id, new BoxCollider{16,16});
    comp->shape = std::make_unique<ShapeRectangle>(ShapeRectangle({16, 16, x, y, Colour{149 + randomNum, 69 + randomNum2, 53 + randomNum3, 100}}));
}
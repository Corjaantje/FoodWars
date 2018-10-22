#include <iostream>
#include <sstream>
#include "../../../Headers/GameECS/Systems/DrawSystem.h"
#include "../../../Headers/GameECS/Systems/IBaseSystem.h"
#include "../../../Headers/GameECS/Components/DrawableComponent.h"
#include "../../../Headers/GameECS/Components/Collider/BoxCollider.h"

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
    _visualFacade->render(_renderList);
}

void DrawSystem::generateTerrain() {
    for(int y=112; y < 480; y+=16) {
        for (int x=0; x < 640; x+=16) {
            if (y >= 160 && x >= 528 && x <= 592) {
                drawComponent(x, y);
            } else if ((y >= 176 && x >= 496)) {
                drawComponent(x, y);
            } else if (y >= 176 && x > 560) {
                drawComponent(x,y);
            } else if (y >= 192 && x >= 464) {
                drawComponent(x,y);
            } else if (y >= 208 && x >= 432) {
                drawComponent(x,y);
            } else if (y >= 224 && x >= 400) {
                drawComponent(x,y);
            } else if (y >= 240 && x >= 368) {
                drawComponent(x,y);
            } else if (y >= 256 && x >= 336) {
                drawComponent(x,y);
            } else if (y >= 192 && x >= 0 && x <= 64 ) {
                drawComponent(x,y);
            } else if (y >= 208 && x >= 0 && x <= 96 ) {
                drawComponent(x,y);
            } else if (y >= 224 && x >= 0 && x <= 112 ) {
                drawComponent(x,y);
            } else if (y >= 256 && x >= 0 && x <= 128 ) {
                drawComponent(x,y);
            } else if (y >= 288 ) {
                drawComponent(x,y);
            }
        }
    }
}

void DrawSystem::drawComponent(int x, int y) {
    int randomNum = rand() % 19 + (-9);
    int randomNum2 = rand() % 19 + (-9);
    int randomNum3 = rand() % 19 + (-9);
    int id = _entityManager->createEntity();
    DrawableComponent *comp = new DrawableComponent();
    _entityManager->addComponentToEntity(id, comp);
    _entityManager->addComponentToEntity(id, new BoxCollider{16,16});
    comp->shape = std::make_unique<ShapeRectangle>(ShapeRectangle({16, 16, x, y, Colour{149 + randomNum, 69 + randomNum2, 53 + randomNum3, 100}}));
}
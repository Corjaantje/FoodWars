#include <utility>
#include <iostream>
#include <sstream>
#include "../../../Headers/GameECS/Systems/DrawSystem.h"
#include "../../../Headers/GameECS/Systems/IBaseSystem.h"
#include "../../../Headers/GameECS/Components/DrawableComponent.h"
#include "../../../Headers/GameECS/Components/Collider/BoxCollider.h"
#include "../../../Headers/GameECS/Components/TurnComponent.h"
#include "../../../Headers/GameECS/Components/PositionComponent.h"

DrawSystem::DrawSystem(std::shared_ptr<EntityManager> entityManager, std::shared_ptr<VisualFacade> visualFacade){
    _entityManager = std::move(entityManager);
    _visualFacade = std::move(visualFacade);
    _timeLast = std::chrono::steady_clock::now().time_since_epoch();
}

DrawSystem::~DrawSystem() = default;

void DrawSystem::update(double dt) {
    std::map<int, std::shared_ptr<DrawableComponent>> drawComps = _entityManager->getAllEntitiesWithComponent<DrawableComponent>();
    _renderList.rectangleList.clear();
    _renderList.spriteList.clear();
    _renderList.textList.clear();
    _updateCallCount++;
    drawNonComponents();
    drawCurrentPlayer();
    //Draw Components
    for(const auto &iterator: _entityManager->getAllEntitiesWithComponent<DrawableComponent>()) {
        std::shared_ptr<PositionComponent> positionComponent = _entityManager->getComponentFromEntity<PositionComponent>(iterator.first);
        if(positionComponent) {
            // todo: scale to match current resolution
            iterator.second->shape->xPos = positionComponent->X;
            iterator.second->shape->yPos = positionComponent->Y;
        }
        iterator.second->shape->addToRender(&_renderList);
    }


    _visualFacade->render(_renderList);
}

void DrawSystem::drawNonComponents() {

    _renderList.spriteList.emplace_back(ShapeSprite{1600, 900, 0, 0, "FoodWarsUISmall.png"});
    if(!_playerIcon.empty()) {
        _renderList.spriteList.emplace_back(ShapeSprite{36, 54, 47, 40, _playerIcon});
    }
    //Framerate
    std::chrono::duration<double> currentTime = std::chrono::steady_clock::now().time_since_epoch();
    double loggen = currentTime.count() - _timeLast.count();
    if (loggen >= 1) {
        _fpsString = "FPS: " + std::to_string(_updateCallCount);
        _timeLast = std::chrono::steady_clock::now().time_since_epoch();
        _updateCallCount = 0;
    }
    if(_showFPS) {
        _renderList.textList.emplace_back(ShapeText(27, 155, _fpsString, 180, 75, 37, Colour(255, 255, 255, 0)));
    }
    //Draw Turn Timer
    for(const auto &iterator: _entityManager->getAllEntitiesWithComponent<TurnComponent>()) {
        if(iterator.second->isMyTurn()){
            double time = iterator.second->getRemainingTime();
            std::string text;
            if(time < 10){
                text = std::to_string(time).substr(0, 3);
            }
            else{
                text = std::to_string(time).substr(0, 4);
            }
            ShapeText timerText {800, 45, text, 180, 75, 37, Colour{255, 255, 255, 0}};
            timerText.addToRender(&_renderList);
            break;
        }
    }
}

void DrawSystem::drawCurrentPlayer() {
    _playerUpdateCount++;
    if(_playerUpdateCount > 30){
        std::map<int, std::shared_ptr<TurnComponent>> turnComps = _entityManager->getAllEntitiesWithComponent<TurnComponent>();
        for (auto const& x : turnComps)
        {
            if(x.second->isMyTurn()){
                ShapeSprite* sprite = dynamic_cast<ShapeSprite*>(_entityManager->getComponentFromEntity<DrawableComponent>(x.first)->shape.get());
                _playerIcon = sprite->imageURL;
            }
        }
        _playerUpdateCount = 0;
    }
}

bool DrawSystem::toggleFpsCounter() {
    _showFPS = !_showFPS;
}
#include "../../../Headers/StateMachine/Misc/LevelBuilder.h"
#include "../../../Headers/GameECS/Components/Collider/BoxColliderComponent.h"
#include "../../../Headers/GameECS/Components/DrawableComponent.h"
#include "../../../../TonicEngine/Headers/Visual/Shapes/ShapeRectangle.h"

LevelBuilder::LevelBuilder() {
    _entityManager = new EntityManager();
}

void LevelBuilder::resetEntityManager() {
    delete _entityManager;
    for(int i=0; i < _momentoList.size(); i++){
        delete _momentoList[i];
    }
    _entityManager = new EntityManager();
}

void LevelBuilder::incrementShapeSize() {
    if(_shapeDimension < MAXIMAL_SHAPE_DIM){
        _shapeDimension++;
    }
}

void LevelBuilder::decrementShapeSize() {
    if(_shapeDimension > MINIMAL_SHAPE_DIM){
        _shapeDimension--;
    }
}

void LevelBuilder::incrementColorRed() {
    _colorRed = (_colorRed + COLOR_INCREMENT % 255);
}

void LevelBuilder::incrementColorGreen() {
    _colorGreen = (_colorGreen + COLOR_INCREMENT % 255);
}

void LevelBuilder::incrementColorBlue() {
    _colorBlue = (_colorBlue + COLOR_INCREMENT % 255);
}

void LevelBuilder::decrementColorRed() {
    if(_colorRed - COLOR_INCREMENT < 0){
        _colorRed = 255 + (_colorRed - COLOR_INCREMENT);
    }
    else{
        _colorRed -= COLOR_INCREMENT;
    }
}

void LevelBuilder::decrementColorGreen() {
    if(_colorGreen - COLOR_INCREMENT < 0){
        _colorGreen = 255 + (_colorGreen - COLOR_INCREMENT);
    }
    else{
        _colorGreen -= COLOR_INCREMENT;
    }
}

void LevelBuilder::decrementColorBlue() {
    if(_colorBlue - COLOR_INCREMENT < 0){
        _colorBlue = 255 + (_colorBlue - COLOR_INCREMENT);
    }
    else{
        _colorBlue -= COLOR_INCREMENT;
    }
}

void LevelBuilder::placeBlock(int x, int y) {
    int convertedX = roundXCoordToGrid(x);
    int convertedY = roundYCoordToGrid(y);
    std::string gridCoord = std::to_string(convertedX) + std::to_string(convertedY);
    if(_CoordinateEntityMap.count(gridCoord) == 0){
        int entity = _entityManager->createEntity();
        auto momento = new EntityMomento(entity);
        _momentoList.push_back(momento);

        if(_buildCollidable){
            _entityManager->addComponentToEntity(entity, new BoxColliderComponent(_shapeDimension, _shapeDimension));
        }
        if(_buildDamageable) {
            //TODO Nog geen damageable component
            //_entityManager->addComponentToEntity(entity, new DamageableComponent());
        }
        auto* drawComp = new DrawableComponent();
        drawComp->shape = std::make_unique<ShapeRectangle>(ShapeRectangle(_shapeDimension, _shapeDimension, convertedX, convertedY, Colour(_colorRed, _colorGreen, _colorBlue, 255)));
        _entityManager->addComponentToEntity(entity, drawComp);
        _CoordinateEntityMap[gridCoord] = entity;
    }
}

void LevelBuilder::undoPlaceBlock() {
    if(_momentoList.back() != 0){
        _entityManager->removeEntity(_momentoList.back()->getState());
        _momentoList.pop_back();
    }
}

Renderlist LevelBuilder::drawCurrentScene() {
    std::map<int, std::shared_ptr<DrawableComponent>> drawComps = _entityManager->getAllEntitiesWithComponent<DrawableComponent>();
    _renderList.rectangleList.clear();
    _renderList.spriteList.clear();
    _renderList.textList.clear();
    int count = drawComps.size();
    for(int i=0; i < drawComps.size(); i++){
        drawComps[i]->shape->addToRender(&_renderList);
    }
    drawMarkedOffArea();
    return _renderList;
}

int LevelBuilder::roundXCoordToGrid(int x) {
    int remainder = x % MINIMAL_SHAPE_DIM;
    if (remainder == 0)
        return x;

    return x - remainder;
}

int LevelBuilder::roundYCoordToGrid(int y) {
    int remainder = y % MINIMAL_SHAPE_DIM;
    if (remainder == 0)
        return y;

    return y - remainder;
}

void LevelBuilder::drawMarkedOffArea() {
    int dim = 8;
    for(int i = 0; i < 1600; i=i+8){
        ShapeRectangle rect(dim, dim, i, 160, Colour(0, 0, 0, 255));
        _renderList.rectangleList.emplace_back(rect);
    }
}
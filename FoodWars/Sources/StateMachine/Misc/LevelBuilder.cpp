#include "../../../Headers/StateMachine/Misc/LevelBuilder.h"
#include "../../../Headers/GameECS/Components/Collider/BoxColliderComponent.h"
#include "../../../Headers/GameECS/Components/DrawableComponent.h"
#include "../../../../TonicEngine/Headers/Visual/Shapes/ShapeRectangle.h"
#include "../../../../TonicEngine/Headers/Visual/Shapes/SpriteButton.h"

LevelBuilder::LevelBuilder() {
    _entityManager = new EntityManager();
    for(int y=0; y < 900; y=y+MINIMAL_SHAPE_DIM){
        this->incrementColorRed();
        for(int x=0; x < 1600; x=x+MINIMAL_SHAPE_DIM){
            this->placeBlock(x, y);
            this->incrementColorBlue();
        }
    }
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
    if(convertedY < BUILDING_LIMIT){
        return;
    }
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

void LevelBuilder::drawCurrentScene(Renderlist &renderlist) {
    std::map<int, std::shared_ptr<DrawableComponent>> drawComps = _entityManager->getAllEntitiesWithComponent<DrawableComponent>();
    renderlist.clearLists();
    int count = drawComps.size();
    for(int i=0; i < drawComps.size(); i++){
        drawComps[i]->shape->addToRender(&renderlist);
    }
    drawMarkedOffArea(renderlist);
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

void LevelBuilder::drawMarkedOffArea(Renderlist &renderlist) {
    int height = 8;
    int width = 1600;
    ShapeRectangle rect(width, height, 0, BUILDING_LIMIT-height, Colour(0, 0, 0, 255));
    renderlist.rectangleList.emplace_back(rect);
    ShapeRectangle rect2(width, height, 0, 900-height, Colour(0, 0, 0, 255));
    renderlist.rectangleList.emplace_back(rect2);
}
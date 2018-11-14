#include "../../../Headers/StateMachine/Misc/LevelBuilder.h"
#include "../../../Headers/GameECS/Components/Collider/BoxCollider.h"
#include "../../../Headers/GameECS/Components/DrawableComponent.h"
#include "../../../../TonicEngine/Headers/Visual/Shapes/ShapeRectangle.h"
#include "../../../../TonicEngine/Headers/Visual/Shapes/SpriteButton.h"

LevelBuilder::LevelBuilder() {
    _entityManager = new EntityManager();
    _wallpaperList.emplace_back("WallpaperCity.png");
    _wallpaperList.emplace_back("WallpaperSky.png");

    _musicList.emplace_back("");
    _selectedMusic = 0;
    _musicList.emplace_back("wildwest");
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

bool LevelBuilder::toggleDamageable() {
    _buildDamageable = !_buildDamageable;
    return _buildDamageable;
}

bool LevelBuilder::toggleCollidable() {
    _buildCollidable = !_buildCollidable;
    return _buildCollidable;
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
            _entityManager->addComponentToEntity(entity, new BoxCollider(_shapeDimension, _shapeDimension));
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

void LevelBuilder::removeBlock(int x, int y) {
    int convertedX = roundXCoordToGrid(x);
    int convertedY = roundYCoordToGrid(y);
    if(convertedY < BUILDING_LIMIT){
        return;
    }
    std::string gridCoord = std::to_string(convertedX) + std::to_string(convertedY);
    if(_CoordinateEntityMap.count(gridCoord) != 0){
        int entityId = _CoordinateEntityMap[gridCoord];
        int it = -1;
        _entityManager->removeEntity(entityId);
        for(int i=0; i< _momentoList.size(); i++){
            if(_momentoList[i]->getState() == entityId){
                it = i;
            }
        }
        if(it != -1){
        _momentoList.erase(_momentoList.begin() + it);
        }
        _CoordinateEntityMap.erase(gridCoord);
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
    for (auto &drawComp : drawComps) {
        drawComp.second->shape->addToRender(&renderlist);
    }
    drawAdditionalItems(renderlist);
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


void LevelBuilder::drawAdditionalItems(Renderlist &renderlist) {
    //TODO TEMP FIX TO MAKE A BACKGROUND WORK.
    ShapeSprite wallpaper(1600, 900, 0, 0, _wallpaperList[_selectedWallpaper]);
    renderlist.backgroundSpriteList.emplace_back(wallpaper);

    int height = 8;
    int width = 1600;
    renderlist.spriteList.emplace_back(ShapeSprite{1600, 900, 0, 0, "WallpaperLevelBuilder.png"});
    ShapeRectangle rect(width, height, 0, BUILDING_LIMIT-height, Colour(0, 0, 0, 255));
    renderlist.rectangleList.emplace_back(rect);
    ShapeRectangle rect2(width, height, 0, 900-height, Colour(0, 0, 0, 255));
    renderlist.rectangleList.emplace_back(rect2);

    ShapeRectangle preview(64, 64, 1200, 60, Colour(_colorRed, _colorGreen, _colorBlue, 255));
    renderlist.rectangleList.emplace_back(preview);
}

void LevelBuilder::setNextWallpaper() {
    if(_wallpaperList.size() > 1){
        int newIndex = (_selectedWallpaper + 1) % _wallpaperList.size();
        _selectedWallpaper = newIndex;
    }
}

void LevelBuilder::setPreviousWallpaper() {
    if(_wallpaperList.size() > 1){
        int newIndex = (_selectedWallpaper - 1);
        if(newIndex < 0){
            newIndex = _wallpaperList.size() - 1;
        }
        _selectedWallpaper = newIndex;
    }
}

void LevelBuilder::setNextMusic() {
    if(_musicList.size() > 1){
        int newIndex = (_selectedMusic + 1) % _musicList.size();
        _selectedMusic = newIndex;
    }
}

void LevelBuilder::setPreviousMusic() {
    if(_musicList.size() > 1){
        int newIndex = (_selectedMusic - 1);
        if(newIndex < 0){
            newIndex = _musicList.size() - 1;
        }
        _selectedMusic = newIndex;
    }
}

std::string LevelBuilder::getSelectedSong() {
    if (_musicList[_selectedMusic].empty()) {
        return "none";
    } else{
        std::string song = _musicList[_selectedMusic];
        return song;
    }
}
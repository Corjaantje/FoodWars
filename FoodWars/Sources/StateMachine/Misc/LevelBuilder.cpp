#include "../../../Headers/StateMachine/Misc/LevelBuilder.h"
#include "../../../Headers/GameECS/Components/Collider/BoxCollider.h"
#include "../../../Headers/GameECS/Components/DrawableComponent.h"

LevelBuilder::LevelBuilder() {
    _entityManager = new EntityManager();

    _musicList.emplace_back("");
    _selectedMusic = 0;
}

void LevelBuilder::resetEntityManager() {
    delete _entityManager;
    for(int i=0; i < _mementoList.size(); i++){
        delete _mementoList[i];
    }
    _entityManager = new EntityManager();
}

EntityManager *LevelBuilder::getEntityManager() {
    return _entityManager;
}
//void LevelBuilder::incrementShapeSize() {
//    if(_shapeDimension < MAXIMAL_SHAPE_DIM){
//        _shapeDimension++;
//    }
//}
//
//void LevelBuilder::decrementShapeSize() {
//    if(_shapeDimension > SHAPE_DIMENSION){
//        _shapeDimension--;
//    }
//}

void LevelBuilder::incrementColorRed() {
    _colorRed = ((_colorRed + COLOR_INCREMENT) % 255);
}

void LevelBuilder::incrementColorGreen() {
    _colorGreen = ((_colorGreen + COLOR_INCREMENT) % 255);
}

void LevelBuilder::incrementColorBlue() {
    _colorBlue = ((_colorBlue + COLOR_INCREMENT) % 255);
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
        auto momento = new EntityMemento(entity);
        _mementoList.push_back(momento);

        if(_buildCollidable){
            _entityManager->addComponentToEntity(entity, new BoxCollider(_shapeDimension, _shapeDimension));
        }
        if(_buildDamageable) {
            //TODO Nog geen damageable component
            //_entityManager->addComponentToEntity(entity, new DamageableComponent());
        }
        auto* drawComp = new DrawableComponent();
        drawComp->shape = new ShapeRectangle(_shapeDimension, _shapeDimension, convertedX, convertedY, Colour(_colorRed, _colorGreen, _colorBlue, 255));
        _entityManager->addComponentToEntity(entity, drawComp);

        _entityManager->addComponentToEntity(entity, new PositionComponent(convertedX, convertedY));
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
        if(entityId == SPAWNPOINT_ID){
            return;
        }
        int it = -1;
        _entityManager->removeEntity(entityId);
        for(int i=0; i< _mementoList.size(); i++){
            if(_mementoList[i]->getState() == entityId){
                it = i;
            }
        }
        if(it != -1){
        _mementoList.erase(_mementoList.begin() + it);
        }
        _CoordinateEntityMap.erase(gridCoord);
    }

}

//void LevelBuilder::undoPlaceBlock() {
//    if(_mementoList.back() != 0){
//        _entityManager->removeEntity(_mementoList.back()->getState());
//        _mementoList.pop_back();
//    }
//}

void LevelBuilder::drawCurrentScene(Renderlist &renderlist) {
    std::map<int, std::shared_ptr<DrawableComponent>> drawComps = _entityManager->getAllEntitiesWithComponent<DrawableComponent>();
    renderlist.clearLists();
    for (auto &drawComp : drawComps) {
        drawComp.second->shape->addToRender(&renderlist);
    }
    drawAdditionalItems(renderlist);
}

int LevelBuilder::roundXCoordToGrid(int x) {
    int remainder = x % SHAPE_DIMENSION;
    if (remainder == 0)
        return x;

    return x - remainder;
}

int LevelBuilder::roundYCoordToGrid(int y) {
    int remainder = y % SHAPE_DIMENSION;
    if (remainder == 0)
        return y;

    return y - remainder;
}

void LevelBuilder::drawAdditionalItems(Renderlist &renderlist) {
    //TODO TEMP FIX TO MAKE A BACKGROUND WORK UNTILL WE HAVE LAYERS.
    renderlist._shapes[0].push_back(createShape<ShapeSprite>(1600, 900, 0, 0, _wallpaperList[_selectedWallpaper]));

    int height = 8;
    int width = 1600;
    renderlist._shapes[2].push_back(createShape<ShapeSprite>(1600, 900, 0, 0, "ScreenLevelBuilder.png"));
    renderlist._shapes[1].push_back(
            createShape<ShapeRectangle>(width, height, 0, BUILDING_LIMIT - height, Colour(0, 0, 0, 255)));
    renderlist._shapes[1].push_back(createShape<ShapeRectangle>(width, height, 0, 900 - height, Colour(0, 0, 0, 255)));
    renderlist._shapes[1].push_back(
            createShape<ShapeRectangle>(64, 64, 1200, 60, Colour(_colorRed, _colorGreen, _colorBlue, 255)));

    for (auto &_spawnPoint : _spawnPoints) {
        renderlist._shapes[1].push_back(
                createShape<ShapeSprite>(SHAPE_DIMENSION, SHAPE_DIMENSION, _spawnPoint.getXCoord(),
                                         _spawnPoint.getYCoord(), "Spawnpoint.png"));
    }
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

std::string LevelBuilder::getCurrentWallpaper() {
    return _wallpaperList[_selectedWallpaper];
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

void LevelBuilder::placeSpawnPoint(int x, int y) {
    int convertedX = roundXCoordToGrid(x);
    int convertedY = roundYCoordToGrid(y);
    if(convertedY < BUILDING_LIMIT){
        return;
    }
    std::string gridCoord = std::to_string(convertedX) + std::to_string(convertedY);
    if(_CoordinateEntityMap.count(gridCoord) == 0){
        Coordinate coord{};
        coord.setCoordinates(convertedX, convertedY);
        _spawnPoints.emplace_back(coord);
        _CoordinateEntityMap[gridCoord] = SPAWNPOINT_ID;
    }

}

void LevelBuilder::removeSpawnPoint(int x, int y) {
    int convertedX = roundXCoordToGrid(x);
    int convertedY = roundYCoordToGrid(y);
    if(convertedY < BUILDING_LIMIT){
        return;
    }
    std::string gridCoord = std::to_string(convertedX) + std::to_string(convertedY);
    if(_CoordinateEntityMap.count(gridCoord) != 0){
        int entityId = _CoordinateEntityMap[gridCoord];
        if(entityId != SPAWNPOINT_ID){
            return;
        }
        int it = -1;
        for(int i = 0; i < _spawnPoints.size(); i++){
            if(_spawnPoints[i].getXCoord() == convertedX && _spawnPoints[i].getYCoord() == convertedY){
                it = i;
            }
        }
        if(it != -1){
            _spawnPoints.erase(_spawnPoints.begin() + it);
            _CoordinateEntityMap.erase(gridCoord);
        }
    }
}

std::vector<Coordinate> LevelBuilder::getSpawnPoints() const {
    return _spawnPoints;
}

GameLevel LevelBuilder::buildConstructedLevel() {
    GameLevel gameLevel{};
    gameLevel.setBackgroundWallpaper(_wallpaperList[_selectedWallpaper]);
    gameLevel.setEntityManager(*_entityManager);
    gameLevel.setSpawnPoints(_spawnPoints);
    gameLevel.setBackgroundMusic(_musicList[_selectedMusic]);
    return gameLevel;
}
void LevelBuilder::addMusicConfig(std::string music) {
    _musicList.emplace_back(music);
}

void LevelBuilder::addWallpaperConfig(std::string wallpaper) {
    _wallpaperList.emplace_back(wallpaper);
}

LevelBuilder::~LevelBuilder() {
    for (IShape *shape: _sprites) {
        delete shape;
    }
    for (EntityMemento *entityMemento: _mementoList) {
        delete entityMemento;
    }
    delete _entityManager;
}

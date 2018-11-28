#include "../../../Headers/StateMachine/Misc/LevelBuilder.h"

LevelBuilder::LevelBuilder(const FileManager &fileManager)
        : _gameLevel(), _entityManager(_gameLevel.getEntityManager()), _selectedMusic(0), _fileManager(&fileManager),
          _colorBlue(0),
          _colorRed(0),
          _colorGreen(0),
          _selectedWallpaper(0) {
    _wallpaperList = _fileManager->getFiles("./Assets/GameWallpapers/", "png", true, false);
    _musicList = _fileManager->getFiles("./Assets/Audio/", "mp3", false, false);

    wallpaper = createShape<ShapeSprite>(1600, 900, 0, 0, _wallpaperList[_selectedWallpaper]);
    wallpaper->layer = 0;

    int height = 8;
    int width = 1600;
    createShape<ShapeSprite>(1600, 900, 0, 0, "ScreenLevelBuilder.png");
    createShape<ShapeRectangle>(width, height, 0, BUILDING_LIMIT - height, Colour(0, 0, 0, 255));
    createShape<ShapeRectangle>(width, height, 0, 900 - height, Colour(0, 0, 0, 255));
    createShape<ShapeRectangle>(64, 64, 1200, 60, Colour(_colorRed, _colorGreen, _colorBlue, 255));
}

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
    if (_colorRed - COLOR_INCREMENT < 0) {
        _colorRed = 255 + (_colorRed - COLOR_INCREMENT);
    } else {
        _colorRed -= COLOR_INCREMENT;
    }
}

void LevelBuilder::decrementColorGreen() {
    if (_colorGreen - COLOR_INCREMENT < 0) {
        _colorGreen = 255 + (_colorGreen - COLOR_INCREMENT);
    } else {
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
    if (_colorBlue - COLOR_INCREMENT < 0) {
        _colorBlue = 255 + (_colorBlue - COLOR_INCREMENT);
    } else {
        _colorBlue -= COLOR_INCREMENT;
    }
}

void LevelBuilder::placeBlock(int x, int y) {
    int convertedX = roundXCoordToGrid(x);
    int convertedY = roundYCoordToGrid(y);
    if (convertedY < BUILDING_LIMIT) {
        return;
    }
    std::string gridCoord = std::to_string(convertedX) + std::to_string(convertedY);
    if (_CoordinateEntityMap.count(gridCoord) == 0) {
        int entity = _entityManager.createEntity();
        auto momento = new EntityMemento(entity);
        _mementoList.push_back(momento);

        if (_buildCollidable) {
            _entityManager.addComponentToEntity<BoxCollider>(entity, _shapeDimension, _shapeDimension);
        }
        if (_buildDamageable) {
            //TODO Nog geen damageable component
            _entityManager.addComponentToEntity<DamageableComponent>(entity, 1);
        }
        _entityManager.addComponentToEntity<DrawableComponent>(entity,
                                                               std::make_unique<ShapeRectangle>(_shapeDimension,
                                                                                                _shapeDimension,
                                                                                                convertedX,
                                                                                                convertedY,
                                                                                                Colour(_colorRed,
                                                                                                       _colorGreen,
                                                                                                       _colorBlue,
                                                                                                       255)));
        _entityManager.addComponentToEntity<PositionComponent>(entity, convertedX, convertedY);
        _CoordinateEntityMap[gridCoord] = entity;
    }
}

void LevelBuilder::removeBlock(int x, int y) {
    int convertedX = roundXCoordToGrid(x);
    int convertedY = roundYCoordToGrid(y);
    if (convertedY < BUILDING_LIMIT) {
        return;
    }
    std::string gridCoord = std::to_string(convertedX) + std::to_string(convertedY);
    if (_CoordinateEntityMap.count(gridCoord) != 0) {
        int entityId = _CoordinateEntityMap[gridCoord];
        if (entityId == SPAWNPOINT_ID) {
            return;
        }
        int it = -1;
        _entityManager.removeEntity(entityId);
        for (int i = 0; i < _mementoList.size(); i++) {
            if (_mementoList[i]->getState() == entityId) {
                it = i;
            }
        }
        if (it != -1) {
            _mementoList.erase(_mementoList.begin() + it);
        }
        _CoordinateEntityMap.erase(gridCoord);
    }

}

void LevelBuilder::drawCurrentScene(Renderlist &renderlist) {
    std::map<int, DrawableComponent *> drawComps = _entityManager.getAllEntitiesWithComponent<DrawableComponent>();
    renderlist.clearLists();
    for (const auto &drawComp : drawComps) {
        drawComp.second->getShape()->addToRender(&renderlist);
    }
    for (const auto &sprite : _sprites) {
        sprite->addToRender(&renderlist);
    }
    for (const auto &spawnSprite : _spawnPointSprites) {
        spawnSprite->addToRender(&renderlist);
    }
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


void LevelBuilder::setNextWallpaper() {
    if (_wallpaperList.size() > 1) {
        int newIndex = (_selectedWallpaper + 1) % _wallpaperList.size();
        _selectedWallpaper = newIndex;
        _gameLevel.setBackgroundWallpaper(_wallpaperList[_selectedWallpaper]);
        wallpaper->imageURL = _wallpaperList[_selectedWallpaper];
    }
}

void LevelBuilder::setPreviousWallpaper() {
    if (_wallpaperList.size() > 1) {
        int newIndex = (_selectedWallpaper - 1);
        if (newIndex < 0) {
            newIndex = _wallpaperList.size() - 1;
        }
        _selectedWallpaper = newIndex;
        _gameLevel.setBackgroundWallpaper(_wallpaperList[_selectedWallpaper]);
        wallpaper->imageURL = _wallpaperList[_selectedWallpaper];
    }
}

std::string LevelBuilder::getCurrentWallpaper() {
    return _wallpaperList[_selectedWallpaper];
}

void LevelBuilder::setNextMusic() {
    if (_musicList.size() > 1) {
        int newIndex = (_selectedMusic + 1) % _musicList.size();
        _selectedMusic = newIndex;
        _gameLevel.setBackgroundMusic(_musicList[_selectedMusic]);
    }
}

void LevelBuilder::setPreviousMusic() {
    if (_musicList.size() > 1) {
        int newIndex = (_selectedMusic - 1);
        if (newIndex < 0) {
            newIndex = _musicList.size() - 1;
        }
        _selectedMusic = newIndex;
        _gameLevel.setBackgroundMusic(_musicList[_selectedMusic]);
    }
}

std::string LevelBuilder::getSelectedSong() const {
    if (_musicList[_selectedMusic].empty()) {
        return "none";
    } else {
        return _musicList[_selectedMusic];
    }
}

void LevelBuilder::placeSpawnPoint(int x, int y) {
    int convertedX = roundXCoordToGrid(x);
    int convertedY = roundYCoordToGrid(y);
    if (convertedY < BUILDING_LIMIT) {
        return;
    }
    std::string gridCoord = std::to_string(convertedX) + std::to_string(convertedY);
    if (_CoordinateEntityMap.count(gridCoord) == 0) {
        Coordinate coord{};
        coord.setCoordinates(convertedX, convertedY);
        _spawnPoints.push_back(coord);
        _spawnPointSprites.push_back(std::make_unique<ShapeSprite>(SHAPE_DIMENSION, SHAPE_DIMENSION, coord.getXCoord(),
                                                                   coord.getYCoord(), "Spawnpoint.png"));
        _CoordinateEntityMap[gridCoord] = SPAWNPOINT_ID;
    }
    _gameLevel.setSpawnPoints(_spawnPoints);
}

void LevelBuilder::removeSpawnPoint(int x, int y) {
    int convertedX = roundXCoordToGrid(x);
    int convertedY = roundYCoordToGrid(y);
    if (convertedY < BUILDING_LIMIT) {
        return;
    }
    std::string gridCoord = std::to_string(convertedX) + std::to_string(convertedY);
    if (_CoordinateEntityMap.count(gridCoord) != 0) {
        int entityId = _CoordinateEntityMap[gridCoord];
        if (entityId != SPAWNPOINT_ID) {
            return;
        }
        for (int i = 0; i < _spawnPoints.size(); i++) {
            if (_spawnPoints[i].getXCoord() == convertedX && _spawnPoints[i].getYCoord() == convertedY) {
                _spawnPoints.erase(_spawnPoints.begin() + i);
                _spawnPointSprites.erase(_spawnPointSprites.begin() + i);
                _CoordinateEntityMap.erase(gridCoord);
                return;
            }
        }
    }
    _gameLevel.setSpawnPoints(_spawnPoints);
}

std::vector<Coordinate> LevelBuilder::getSpawnPoints() const {
    return _spawnPoints;
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
}

const GameLevel &LevelBuilder::getConstructedLevel() const {
    return _gameLevel;
}

GameLevel &LevelBuilder::getConstructedLevelNonConst() {
    std::cerr << "LevelBuilder Line 310: This needs to be const! Which means the saving function must be const."
              << std::endl;
    return _gameLevel;
}
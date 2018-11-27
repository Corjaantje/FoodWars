#ifndef PROJECT_SWA_LEVELBUILDER_H
#define PROJECT_SWA_LEVELBUILDER_H


#include "../../GameECS/Entities/EntityManager.h"
#include "EntityMemento.h"
#include "../../../../TonicEngine/Headers/Visual/Renderlist.h"
#include "GameLevel.h"
#include "../../GameECS/Systems/StorageSystem.h"
#include "../../../../TonicEngine/Headers/Storage/FileManager.h"

const int SHAPE_DIMENSION = 32;
//const int MAXIMAL_SHAPE_DIM = 64;
const int COLOR_INCREMENT = 10;
const int BUILDING_LIMIT = 192;
const int SPAWNPOINT_ID = -1;

class LevelBuilder {
public:
    explicit LevelBuilder(const FileManager& fileManager);
    ~LevelBuilder();
private:
    EntityManager* _entityManager;
    std::vector<EntityMemento*> _mementoList;
    std::map<std::string, int> _CoordinateEntityMap;
    std::vector<Coordinate> _spawnPoints;
    std::vector<std::unique_ptr<ShapeSprite>> _spawnPointSprites;
    bool _buildCollidable = true;
    bool _buildDamageable = true;

    int _shapeDimension = SHAPE_DIMENSION;

    const FileManager* _fileManager;
    int _colorRed; //Between 0 and 255
    int _colorGreen; //Between 0 and 255
    int _colorBlue; //Between 0 and 255

    std::vector<std::string> _wallpaperList;
    int _selectedWallpaper;

    std::vector<std::string> _musicList;
    int _selectedMusic;
    std::vector<IShape *> _sprites;
    ShapeSprite* wallpaper;

    template<typename T, typename... Args>
    T *createShape(Args &&... args) {
        T *shape = new T(std::forward<Args>(args)...);
        _sprites.push_back(shape);
        return shape;
    }
public:
    void resetEntityManager();
    EntityManager* getEntityManager();

//    void incrementShapeSize();
//    void decrementShapeSize();

    void incrementColorRed();
    void incrementColorGreen();
    void incrementColorBlue();

    void decrementColorRed();
    void decrementColorGreen();
    void decrementColorBlue();

    void placeBlock(int x, int y);
    void removeBlock(int x, int y);
//    void undoPlaceBlock();

    void placeSpawnPoint(int x, int y);
    void removeSpawnPoint(int x, int y);
    std::vector<Coordinate> getSpawnPoints() const;

    bool toggleCollidable();
    bool toggleDamageable();

    void setNextWallpaper();
    void setPreviousWallpaper();
    std::string getCurrentWallpaper();

    void setNextMusic();
    void setPreviousMusic();
    std::string getSelectedSong();
    void drawCurrentScene(Renderlist &renderlist);

    GameLevel buildConstructedLevel();
private:
    int roundXCoordToGrid(int x);
    int roundYCoordToGrid(int y);
};


#endif //PROJECT_SWA_LEVELBUILDER_H

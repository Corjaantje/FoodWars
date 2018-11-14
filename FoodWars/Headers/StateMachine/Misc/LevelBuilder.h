#ifndef PROJECT_SWA_LEVELBUILDER_H
#define PROJECT_SWA_LEVELBUILDER_H


#include "../../GameECS/Entities/EntityManager.h"
#include "EntityMomento.h"
#include "../../../../TonicEngine/Headers/Visual/Renderlist.h"
#include "GameLevel.h"

const int MINIMAL_SHAPE_DIM = 32;
const int MAXIMAL_SHAPE_DIM = 64;
const int COLOR_INCREMENT = 10;
const int BUILDING_LIMIT = 192;
const int SPAWNPOINT_ID = -1;

class LevelBuilder {
public:
    LevelBuilder();
    ~LevelBuilder() = default;
private:
    EntityManager* _entityManager = nullptr;
    std::vector<EntityMomento*> _momentoList;
    std::map<std::string, int> _CoordinateEntityMap;
    std::vector<Coordinate> _spawnPoints;
    bool _buildCollidable = false;
    bool _buildDamageable = false;

    int _shapeDimension = MINIMAL_SHAPE_DIM;

    int _colorRed = 0; //Between 0 and 255
    int _colorGreen = 0; //Between 0 and 255
    int _colorBlue = 0; //Between 0 and 255

    std::vector<std::string> _wallpaperList;
    int _selectedWallpaper = 0;

    std::vector<std::string> _musicList;
    int _selectedMusic = 0;
public:
    void resetEntityManager();

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

    void placeSpawnsPoint(int x, int y);
    void removeSpawnpPoint(int x, int y);

    bool toggleCollidable();
    bool toggleDamageable();

    void setNextWallpaper();
    void setPreviousWallpaper();

    void setNextMusic();
    void setPreviousMusic();
    std::string getSelectedSong();
    void drawCurrentScene(Renderlist &renderlist);

    void addWallpaperConfig(std::string music);
    void addMusicConfig(std::string wallpaper);

    GameLevel buildConstructedLevel();
private:
    int roundXCoordToGrid(int x);
    int roundYCoordToGrid(int y);

    void drawAdditionalItems(Renderlist &renderlist);
};


#endif //PROJECT_SWA_LEVELBUILDER_H

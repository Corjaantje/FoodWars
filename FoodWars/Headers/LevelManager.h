#ifndef PROJECT_SWA_LEVELMANAGER_H
#define PROJECT_SWA_LEVELMANAGER_H

#include "GameECS/Entities/EntityManager.h"
#include "GameECS/Components/DrawableComponent.h"
#include "GameECS/Components/TurnComponent.h"
#include "GameECS/Components/GravityComponent.h"
#include "../../TonicEngine/Headers/Visual/Shapes/ShapeSprite.h"
#include "GameECS/Components/Collider/BoxCollider.h"

class LevelManager {
private:
    void generateTerrainDrawables(int x, int y);
    void generateTerrain();
public:
    LevelManager();
    ~LevelManager();
    EntityManager startLevel(int level);
    EntityManager _entityManager;

};
#endif //PROJECT_SWA_LEVELMANAGER_H

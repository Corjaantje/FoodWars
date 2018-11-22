#ifndef PROJECT_SWA_ANIMATIONMANAGER_H
#define PROJECT_SWA_ANIMATIONMANAGER_H

#include <vector>
#include <string>
#include "../../TonicEngine/Headers/Visual/Shapes/IShape.h"
#include "../../TonicEngine/Headers/Visual/Shapes/ShapeSprite.h"

class AnimationManager {
private:
    std::string getTeamImage(int team)const;
public:
    AnimationManager() = default;
    ~AnimationManager() = default;
    std::vector<IShape*> moveLeftAnimation(int width, int height, int xPos, int yPos, int team)const;
    std::vector<IShape*> moveRightAnimation(int width, int height, int xPos, int yPos, int team)const;
    std::vector<IShape*> lookLeftAnimation(int width, int height, int xPos, int yPos, int team)const;
    std::vector<IShape*> lookRightAnimation(int width, int height, int xPos, int yPos, int team)const;
    std::vector<IShape*> jumpLeftAnimation(int width, int height, int xPos, int yPos, int team)const;
    std::vector<IShape*> jumpRightAnimation(int width, int height, int xPos, int yPos, int team)const;
};


#endif //PROJECT_SWA_ANIMATIONMANAGER_H
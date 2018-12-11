#include "../Headers/AnimationManager.h"

std::string AnimationManager::getTeamImage(Faction faction) const{
    //TODO: Pass animatable item and check if player or item and return correct starting name
    std::string teamString = "Player";
    // Check for team
    if(faction == Faction::WHITE)
        teamString += "W";
    else if(faction == Faction::YELLOW)
        teamString += "Y";
    else if(faction == Faction::GREEN)
        teamString += "G";
    else if(faction == Faction::RED)
        teamString += "R";
    teamString += "_";

    return teamString;
}

// Returns list of sprites for a left walking animation
std::vector<std::unique_ptr<IShape>>
AnimationManager::moveLeftAnimation(int width, int height, int xPos, int yPos, Faction faction) const {
    std::vector<std::unique_ptr<IShape>> animation;
    std::string teamImage = getTeamImage(faction);
    animation.push_back(std::make_unique<ShapeSprite>(width, height, xPos, yPos, teamImage + "L1.png"));
    animation.push_back(std::make_unique<ShapeSprite>(width, height, xPos, yPos, teamImage + "L2.png"));
    return animation;
}

// Returns list of sprites for a right walking animation
std::vector<std::unique_ptr<IShape>>
AnimationManager::moveRightAnimation(int width, int height, int xPos, int yPos, Faction faction) const {
    std::vector<std::unique_ptr<IShape>> animation;
    std::string teamImage = getTeamImage(faction);
    animation.push_back(std::make_unique<ShapeSprite>(width, height, xPos, yPos, teamImage + "R1.png"));
    animation.push_back(std::make_unique<ShapeSprite>(width, height, xPos, yPos, teamImage + "R2.png"));
    return animation;
}

// Returns list of sprites for a left looking animation
std::vector<std::unique_ptr<IShape>>
AnimationManager::lookLeftAnimation(int width, int height, int xPos, int yPos, Faction faction) const {
    std::vector<std::unique_ptr<IShape>> animation;
    std::string teamImage = getTeamImage(faction);
    animation.push_back(std::make_unique<ShapeSprite>(width, height, xPos, yPos, teamImage + "L0.png"));
    return animation;
}

// Returns list of sprites for a right looking animation
std::vector<std::unique_ptr<IShape>>
AnimationManager::lookRightAnimation(int width, int height, int xPos, int yPos, Faction faction) const {
    std::vector<std::unique_ptr<IShape>> animation;
    std::string teamImage = getTeamImage(faction);
    animation.push_back(std::make_unique<ShapeSprite>(width, height, xPos, yPos, teamImage + "R0.png"));
    return animation;
}

// Returns list of sprites for a left jumping animation
std::vector<std::unique_ptr<IShape>>
AnimationManager::jumpLeftAnimation(int width, int height, int xPos, int yPos, Faction faction) const {
    std::vector<std::unique_ptr<IShape>> animation;
    std::string teamImage = getTeamImage(faction);
    animation.push_back(std::make_unique<ShapeSprite>(width, height, xPos, yPos, teamImage + "L1.png"));
    return animation;
}

// Returns list of sprites for a right jumping animation
std::vector<std::unique_ptr<IShape>>
AnimationManager::jumpRightAnimation(int width, int height, int xPos, int yPos, Faction faction) const {
    std::vector<std::unique_ptr<IShape>> animation;
    std::string teamImage = getTeamImage(faction);
    animation.push_back(std::make_unique<ShapeSprite>(width, height, xPos, yPos, teamImage + "R1.png"));
    return animation;
}
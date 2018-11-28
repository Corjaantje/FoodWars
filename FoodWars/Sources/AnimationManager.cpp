#include "../Headers/AnimationManager.h"

std::string AnimationManager::getTeamImage(int team) const{
    //TODO: Pass animatable item and check if player or item and return correct starting name
    std::string teamString = "Player";
    // Check for team
    if(team == 0)
        teamString += "W";
    else if(team == 1)
        teamString += "Y";
    else if(team == 2)
        teamString += "G";
    teamString += "_";

    return teamString;
}

// Returns list of sprites for a left walking animation
std::vector<std::unique_ptr<IShape>>
AnimationManager::moveLeftAnimation(int width, int height, int xPos, int yPos, int team) const {
    std::vector<std::unique_ptr<IShape>> animation;
    std::string teamImage = getTeamImage(team);
    animation.push_back(std::make_unique<ShapeSprite>(width, height, xPos, yPos, teamImage + "L1.png"));
    animation.push_back(std::make_unique<ShapeSprite>(width, height, xPos, yPos, teamImage + "L2.png"));
    return animation;
}

// Returns list of sprites for a right walking animation
std::vector<std::unique_ptr<IShape>>
AnimationManager::moveRightAnimation(int width, int height, int xPos, int yPos, int team) const {
    std::vector<std::unique_ptr<IShape>> animation;
    std::string teamImage = getTeamImage(team);
    animation.push_back(std::make_unique<ShapeSprite>(width, height, xPos, yPos, teamImage + "R1.png"));
    animation.push_back(std::make_unique<ShapeSprite>(width, height, xPos, yPos, teamImage + "R2.png"));
    return animation;
}

// Returns list of sprites for a left looking animation
std::vector<std::unique_ptr<IShape>>
AnimationManager::lookLeftAnimation(int width, int height, int xPos, int yPos, int team) const {
    std::vector<std::unique_ptr<IShape>> animation;
    std::string teamImage = getTeamImage(team);
    animation.push_back(std::make_unique<ShapeSprite>(width, height, xPos, yPos, teamImage + "L0.png"));
    return animation;
}

// Returns list of sprites for a right looking animation
std::vector<std::unique_ptr<IShape>>
AnimationManager::lookRightAnimation(int width, int height, int xPos, int yPos, int team) const {
    std::vector<std::unique_ptr<IShape>> animation;
    std::string teamImage = getTeamImage(team);
    animation.push_back(std::make_unique<ShapeSprite>(width, height, xPos, yPos, teamImage + "R0.png"));
    return animation;
}

// Returns list of sprites for a left jumping animation
std::vector<std::unique_ptr<IShape>>
AnimationManager::jumpLeftAnimation(int width, int height, int xPos, int yPos, int team) const {
    std::vector<std::unique_ptr<IShape>> animation;
    std::string teamImage = getTeamImage(team);
    animation.push_back(std::make_unique<ShapeSprite>(width, height, xPos, yPos, teamImage + "L1.png"));
    return animation;
}

// Returns list of sprites for a right jumping animation
std::vector<std::unique_ptr<IShape>>
AnimationManager::jumpRightAnimation(int width, int height, int xPos, int yPos, int team) const {
    std::vector<std::unique_ptr<IShape>> animation;
    std::string teamImage = getTeamImage(team);
    animation.push_back(std::make_unique<ShapeSprite>(width, height, xPos, yPos, teamImage + "R1.png"));
    return animation;
}
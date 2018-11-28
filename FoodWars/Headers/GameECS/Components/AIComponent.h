#ifndef PROJECT_SWA_AICOMPONENT_H
#define PROJECT_SWA_AICOMPONENT_H

#include "Component.h"

class AIComponent : public Component{
private:
    int _difficulty;
public:
    explicit AIComponent(int difficulty);
    int getDifficulty() const;
};

#endif //PROJECT_SWA_AICOMPONENT_H
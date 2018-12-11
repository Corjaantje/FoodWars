#ifndef PROJECT_SWA_FACTIONCOMPARER_H
#define PROJECT_SWA_FACTIONCOMPARER_H

#include <unordered_map>
#include "../../../StateMachine/Misc/FactionEnum.h"

class FactionComparer {
public:
    FactionComparer();
    ~FactionComparer();
    const Faction* getWeakness(const Faction& faction) const;
    const Faction* getStrength(const Faction& faction) const;
private:
    std::unordered_map<Faction, Faction> _weaknessMap;
    std::unordered_map<Faction, Faction> _strengthMap;
};
#endif //PROJECT_SWA_FACTIONCOMPARER_H

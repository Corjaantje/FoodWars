#ifndef PROJECT_SWA_TURNSYSTEM_H
#define PROJECT_SWA_TURNSYSTEM_H

#include "IBaseSystem.h"
#include "../Components/TurnComponent.h"
#include "../Components/DrawableComponent.h"
#include "../Events/TurnSwitchedEvent.h"
#include "../../../../TonicEngine/Headers/Input/IObservable.h"

class TurnSystem : public IBaseSystem, public IObservable<TurnSwitchedEvent> {
private:
    int _defaultTimePerTurn;
    int _timePerTurn;
    EntityManager *_entityManager;
public:
    explicit TurnSystem(EntityManager &entityManager);
    ~TurnSystem() override;
    void switchTurn();
    void resetCurrentTime();
    void resetCurrentEnergy();
    int getCurrentPlayerID() const;
    double getCurrentPlayerEnergy() const;
    void update(double deltaTime) override;
private:
    void createCurrentPlayerHighlight(int entityID);
    void resetPlayerHighlight(double deltaTime);
    int _currentHighlightEntityId = -1;
    double _timePerUpdateHighlight = 0;
};


#endif //PROJECT_SWA_TURNSYSTEM_H

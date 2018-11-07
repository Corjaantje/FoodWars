#include "../../../Headers/StateMachine/Misc/EntityMomento.h"

EntityMomento::EntityMomento(int entityID) {
    _entityId = entityID;
}

int EntityMomento::getState() const {
    return _entityId;
}
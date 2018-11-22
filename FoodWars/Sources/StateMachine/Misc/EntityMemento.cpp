#include "../../../Headers/StateMachine/Misc/EntityMemento.h"

EntityMemento::EntityMemento(int entityID) {
    _entityId = entityID;
}

int EntityMemento::getState() const {
    return _entityId;
}
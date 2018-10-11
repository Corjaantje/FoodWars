#include "../../../Headers/GameECS/Entities/EntityWithComponent.h"

EntityWithComp::EntityWithComp(int entityId, Component component) {
    _id = entityId;
    _component = component;
}
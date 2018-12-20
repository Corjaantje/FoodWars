#include <algorithm>
#include "../../../Headers/GameECS/Entities/EntityManager.h"

EntityManager::EntityManager() : _componentsByClass(), _lowestUnassignedEntityId(-1) {

}

EntityManager::~EntityManager() = default;

int EntityManager::createEntity() {
    return ++_lowestUnassignedEntityId;
}

void EntityManager::removeEntity(int entityId) {
    for (auto &iterator : _componentsByClass) {
        std::string key = iterator.first;
        iterator.second.erase(entityId);
    }
}

bool EntityManager::exists(int entityId) const {
    for (auto &iterator : _componentsByClass) {
        if (iterator.second.find(entityId) != iterator.second.end()) {
            return true;
        }
    }
    return false;
}

std::map<int, std::vector<Component *>> EntityManager::getAllEntitiesWithAllComponents() const {
    std::map<int, std::vector<Component *>> componentsOfEntities;
    //construct map where all components of an entity are grouped
    for (const auto &iterator: _componentsByClass) {
        for (const auto &componentIterator: iterator.second) {
            componentsOfEntities[componentIterator.first].push_back(componentIterator.second.get());
        }
    }
    return componentsOfEntities;
}
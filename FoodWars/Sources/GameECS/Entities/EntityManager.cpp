#include "../../../Headers/GameECS/Entities/EntityManager.h"
#include <typeinfo>
EntityManager::EntityManager() {
    _lowestUnassignedEntityId = -1;
}

EntityManager::~EntityManager() = default;

int EntityManager::createEntity(Component components[], int size) {
    _entities.push_back(_lowestUnassignedEntityId++);
    for(int i=0; i < size; i++){
        //addComponentToEntity(_lowestUnassignedEntityId, components[i]);
    }
}

template <typename Comp> void EntityManager::removeComponentFromEntity(Component component, int entityId) {
    _componentsByClass.erase(typeid(component).name());
}

void EntityManager::removeEntity(int entityId) {
    _entities.remove(entityId);
    for (auto &_componentsByClas : _componentsByClass) {
        std::string k = _componentsByClas.first;
        /*std::map<int, Component*> _temp = _componentsByClass[k];
        _temp.erase(entityId);*/
    }
}
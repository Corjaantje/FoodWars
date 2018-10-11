#include "../../../Headers/GameECS/Entities/EntityManager.h"
#include <typeinfo>
EntityManager::EntityManager() {
    _lowestUnassignedEntityId = -1;
}

EntityManager::~EntityManager() = default;

int EntityManager::createEntity(Component components[], int size) {
    _entities.push_back(_lowestUnassignedEntityId++);
    for(int i=0; i < size; i++){
        addComponentToEntity(_lowestUnassignedEntityId, components[i]);
    }
}

void EntityManager::addComponentToEntity(int entity, Component component) {
    std::string componentType = typeid(component).name();
    if(!_componentsByClass.count(componentType)){
        _componentsByClass[componentType] = map<int, Component>();
    }
    _componentsByClass[componentType][entity] = component;
}

template <typename Comp> void EntityManager::removeComponentFromEntity(Component component, int entityId) {
    _componentsByClass.erase(typeid(component).name());
}

template <typename Comp> Comp EntityManager::getComponent(int entityId) {
    string name = typeid(Comp).name();
    if (_componentsByClass.count(name) > 0)
        return (Comp)_componentsByClass[name][entityId];
    else
        return nullptr;
}

void EntityManager::removeEntity(int entityId) {
    _entities.remove(entityId);
    for (auto &_componentsByClas : _componentsByClass) {
        std::string k = _componentsByClas.first;
        map<int, Component> _temp = _componentsByClass[k];
        _temp.erase(entityId);
    }
}
#include "../../../Headers/GameECS/Entities/EntityManager.h"
#include <typeinfo>
EntityManager::EntityManager() {
    _lowestUnassignedEntityId = -1;
}

EntityManager::~EntityManager() {
}

int EntityManager::createEntity(Component components[], int size) {
    _entities.push_back(_lowestUnassignedEntityId++);
    for(int i=0; i < size; i++){
        addComponentToEntity(_lowestUnassignedEntityId, components[i]);
    }
}

void EntityManager::addComponentToEntity(int entity, Component component) {
    std::string componentType = typeid(component).name();
    if(!_componentsByClass.count(componentType)){
        _componentsByClass[componentType] = vector<Component>();
    }
    _componentsByClass[componentType][entity] = component;
}

template <typename Component> void EntityManager::removeComponentFromEntity(Component component, int entityId) {
    _componentsByClass.erase(typeid(component).name());
}

template <typename Component> Component EntityManager::getComponent(int entityId) {
    string name = typeid(Component).name();
    if (_componentsByClass.count(name) > 0)
        return (Component)_componentsByClass[name][entityId];
    else
        return nullptr;
}

void EntityManager::removeEntity(int entityId) {
    _entities.remove(entityId);
    for(std::map<std::string, vector<Component>>::iterator iter = _componentsByClass.begin(); iter != _componentsByClass.end(); ++iter)
    {
        std::string k =  iter->first;
        _componentsByClass[k].erase(iter->second.begin() + entityId);
    }
}
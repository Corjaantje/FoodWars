#ifndef PROJECT_SWA_ENTITYMANAGER_H
#define PROJECT_SWA_ENTITYMANAGER_H


#include <map>
#include <list>
#include <vector>
#include "../Components/Component.h"
#include <typeinfo>
#include <iostream>

class EntityManager {
private:
    int _lowestUnassignedEntityId;
    std::list<int> _entities;
    std::map<std::string, std::map<int, Component*>> _componentsByClass;
public:
    EntityManager();
    ~EntityManager();
    int createEntity(Component components[], int size);
    template <typename Comp> void addComponentToEntity(int entity, Comp component)
    {
        std::string componentType = typeid(Comp).name();
        if(!_componentsByClass.count(componentType)){
            _componentsByClass[componentType] = std::map<int, Component*>();
        }
        _componentsByClass[componentType][entity] = &component;
    }
    template <typename Comp> void removeComponentFromEntity(Component component, int entityId);
    template <typename Comp> Comp* getComponentFromEntity(int entityId) {
        std::string name = typeid(Comp).name();
        if (_componentsByClass.count(name) > 0)
            return static_cast<Comp*>(_componentsByClass[name][entityId]);
        else
            return nullptr;
    }

    template <typename Comp> std::map<int, Component*> getAllEntitiesWithComponent() {
        std::string className = typeid(Comp).name();
        if(_componentsByClass.count(className) > 0){
            return static_cast<std::map<int, Component*>>(_componentsByClass[className]);
            //return map<int, Comp*>();
        }
        else{
            return std::map<int, Component*>();
        }
    }

    void removeEntity(int entityId);
};


#endif //PROJECT_SWA_ENTITYMANAGER_H

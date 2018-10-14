#ifndef PROJECT_SWA_ENTITYMANAGER_H
#define PROJECT_SWA_ENTITYMANAGER_H


#include <map>
#include <list>
#include <vector>
#include "../Components/Component.h"
#include "EntityWithComponent.h"
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
    template <typename Comp> void addComponentToEntity(int entity, Comp* component)
    {
        std::string componentType = typeid(Comp).name();
        if(!_componentsByClass.count(componentType)){
            _componentsByClass[componentType] = std::map<int, Component*>();
        }
        _componentsByClass[componentType][entity] = component;
    }
    template <typename Comp> void removeComponentFromEntity(Component component, int entityId);

    template <typename Comp> EntityWithComponent<Comp> getComponentFromEntity(int entityId) {
        std::string name = typeid(Comp).name();
        if (_componentsByClass.count(name) > 0)
            return EntityWithComponent<Comp>(entityId, std::shared_ptr<Comp>(static_cast<Comp*>(_componentsByClass[name][entityId])));
        else
            return EntityWithComponent<Comp>(entityId, nullptr);
    }

    template <typename Comp> std::vector<EntityWithComponent<Comp>> getAllEntitiesWithComponent() {
        std::string className = typeid(Comp).name();
        if(_componentsByClass.count(className) > 0){
            //return static_cast<std::vector<EntityWithComponent<Comp>>>(_componentsByClass[className]);
            std::vector<EntityWithComponent<Comp>> entities;
            for (auto &iterator : _componentsByClass[className]) {
                entities.push_back(EntityWithComponent<Comp>{iterator.first, std::shared_ptr<Comp>(static_cast<Comp*>(iterator.second))});
            }
            return entities;
        }
        else{
            return std::vector<EntityWithComponent<Comp>>();
        }
    }

    void removeEntity(int entityId);
};


#endif //PROJECT_SWA_ENTITYMANAGER_H

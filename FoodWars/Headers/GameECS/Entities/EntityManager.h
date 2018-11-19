#ifndef PROJECT_SWA_ENTITYMANAGER_H
#define PROJECT_SWA_ENTITYMANAGER_H

#include "memory"
#include <map>
#include <vector>
#include "../Components/Component.h"
#include <typeinfo>
#include <iostream>

class EntityManager {
private:
    int _lowestUnassignedEntityId;
    std::map<std::string, std::map<int, std::shared_ptr<Component>>> _componentsByClass;
public:
    EntityManager();
    ~EntityManager();
    int createEntity();
    int createEntity(Component components[], int size);
    template <typename Comp> void addComponentToEntity(int entity, Comp* component)
    {
        std::string componentType = typeid(Comp).name();
        if(!_componentsByClass.count(componentType)){
            _componentsByClass[componentType] = std::map<int, std::shared_ptr<Component>>();
        }
        _componentsByClass[componentType][entity] = std::shared_ptr<Component>(component);
    }

    template <typename Comp> void removeComponentFromEntity(int entityId) {
        std::string className = typeid(Comp).name();
        _componentsByClass[className].erase(entityId);
    }

    template <typename Comp> std::shared_ptr<Comp> getComponentFromEntity(int entityId) {
        std::string name = typeid(Comp).name();
        if (_componentsByClass.count(name) > 0)
            return std::dynamic_pointer_cast<Comp>(_componentsByClass[name][entityId]);
        return nullptr;
    }

    template <typename Comp> std::map<int, std::shared_ptr<Comp>> getAllEntitiesWithComponent() {
        std::string className = typeid(Comp).name();
        std::map<int, std::shared_ptr<Comp>> returnMap;
        if(_componentsByClass.count(className) > 0){
            for(auto const &iterator: _componentsByClass[className]) {
                returnMap[iterator.first] = std::dynamic_pointer_cast<Comp>(iterator.second);
            }
        }
        return returnMap;
    }

    void removeEntity(int entityId);
    bool exists(int entityId);
};


#endif //PROJECT_SWA_ENTITYMANAGER_H

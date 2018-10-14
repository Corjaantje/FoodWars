#ifndef PROJECT_SWA_ENTITYMANAGER_H
#define PROJECT_SWA_ENTITYMANAGER_H


#include <map>
#include <list>
#include <vector>
#include "../Components/Component.h"
#include <typeinfo>

using namespace std;

class EntityManager {
private:
    int _lowestUnassignedEntityId;
    list<int> _entities;
    map<std::string, map<int, Component>> _componentsByClass;
public:
    EntityManager();
    ~EntityManager();
    int createEntity(Component components[], int size);
    template <typename Comp> void addComponentToEntity(int entity, Comp component)
    {
        std::string componentType = typeid(Comp).name();
        if(!_componentsByClass.count(componentType)){
            _componentsByClass[componentType] = map<int, Comp>();
        }
        _componentsByClass[componentType][entity] = component;
    }
    template <typename Comp> void removeComponentFromEntity(Component component, int entityId);
    template <typename Comp> Comp getComponent(int entityId);
    template <typename Comp> map<int, Comp> getAllEntities() {
        std::string className = typeid(Comp).name();
        if(_componentsByClass.count(className) > 0){
            return dynamic_cast<map<int, Comp>>(_componentsByClass[className]);
        }
        else{
            return map<int, Comp>();
        }
    }

    void removeEntity(int entityId);
};


#endif //PROJECT_SWA_ENTITYMANAGER_H

#ifndef PROJECT_SWA_ENTITYMANAGER_H
#define PROJECT_SWA_ENTITYMANAGER_H


#include <map>
#include <list>
#include <vector>
#include "../Components/Component.h"
using namespace std;

class EntityManager {
private:
    int _lowestUnassignedEntityId;
    list<int> _entities;
    map<std::string, vector<Component>> _componentsByClass;
public:
    EntityManager();
    ~EntityManager();
    int createEntity(Component components[], int size);
    void addComponentToEntity(int entity, Component component);
    template <typename Component> void removeComponentFromEntity(Component component, int entityId);
    template <typename Component> Component getComponent(int entityId);
    void removeEntity(int entityId);
};


#endif //PROJECT_SWA_ENTITYMANAGER_H

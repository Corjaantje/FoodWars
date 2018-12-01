#ifndef PROJECT_SWA_ENTITYMANAGER_H
#define PROJECT_SWA_ENTITYMANAGER_H

#include "memory"
#include <map>
#include <vector>
#include "../Components/Component.h"
#include <typeinfo>
#include <iostream>
#include <unordered_map>

class EntityManager {
private:
    int _lowestUnassignedEntityId;
    std::unordered_map<std::string, std::map<int, std::unique_ptr<Component>>> _componentsByClass; //todo: maybe use unordered_map
public:
    EntityManager();

    ~EntityManager();

    EntityManager(const EntityManager &other) = delete;

    EntityManager &operator=(const EntityManager &other) = delete;

    int createEntity();

    int createEntity(Component components[], int size);

    /*template<typename Comp>
    void addComponentToEntity(int entity, const Comp& component) {
        std::string componentType = typeid(Comp).name();
        //_componentsByClass[componentType][entity] = std::make_unique<Comp>(component);
    }*/

    template<typename Comp, typename... Args>
    Comp &addComponentToEntity(int entity, Args &&... args) {
        std::string componentType = typeid(Comp).name();
        _componentsByClass[componentType][entity] = std::make_unique<Comp>(std::forward<Args>(args)...);
        return *static_cast<Comp *>(_componentsByClass[componentType][entity].get());
    }

    template<typename Comp>
    void removeComponentFromEntity(int entityId) {
        std::string className = typeid(Comp).name();
        _componentsByClass[className].erase(entityId);
    }

    template<typename Comp>
    Comp *getComponentFromEntity(int entityId) const {
        std::string name = typeid(Comp).name();
        if (_componentsByClass.count(name) > 0 && _componentsByClass.at(name).count(entityId) > 0)
            return static_cast<Comp *>(_componentsByClass.at(name).at(entityId).get());
        return nullptr;
    }

    template<typename Comp>
    std::map<int, Comp *>
    getAllEntitiesWithComponent() const { //todo: return transform iterator so we don't have to loop through the list of components only to cast to the needed type
        std::string className = typeid(Comp).name();
        std::map<int, Comp *> returnMap;
        if (_componentsByClass.count(className) > 0) {
            for (auto const &iterator: _componentsByClass.at(className)) {
                returnMap[iterator.first] = static_cast<Comp*>(iterator.second.get());
            }
        }
        return returnMap;
    }

    void removeEntity(int entityId);

    bool exists(int entityId) const;
};

#endif //PROJECT_SWA_ENTITYMANAGER_H

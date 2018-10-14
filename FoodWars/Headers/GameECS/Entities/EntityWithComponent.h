//
// Created by Lucas on 14/10/2018.
//

#ifndef PROJECT_SWA_ENTITYWITHCOMPONENT_H
#define PROJECT_SWA_ENTITYWITHCOMPONENT_H

#include "memory"

template <typename ComponentType>
class EntityWithComponent {
private:
    int _entityId;
    std::shared_ptr<ComponentType> _component;
public:
    int getEntityId() {
        return 0;
    }
    /*EntityWithComponent(const EntityWithComponent& other) {
        _entityId = other._entityId;
        _component = other._component;
    };
    EntityWithComponent& operator=(const EntityWithComponent& other) {
        if(this != other) {
            _entityId = other._entityId;
            _component = other._component;
        }
        return *this;
    };
    ~EntityWithComponent() {

    };*/

    std::shared_ptr<ComponentType> getComponent() {
        return _component;
    }


    EntityWithComponent(int entityId, std::shared_ptr<ComponentType> component) : _entityId(entityId), _component(component) {

    }


};
#endif //PROJECT_SWA_ENTITYWITHCOMPONENT_H

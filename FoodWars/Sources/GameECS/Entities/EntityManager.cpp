#include <algorithm>
#include "../../../Headers/GameECS/Entities/EntityManager.h"

EntityManager::EntityManager() : _componentsByClass(), _lowestUnassignedEntityId(-1) {

}

EntityManager::~EntityManager() = default;

int EntityManager::createEntity() {
    return ++_lowestUnassignedEntityId;
}

/*int EntityManager::createEntity(Component components[], int size) {
    for(int i=0; i < size; i++){
        // kan momenteel niet, omdat de name van de components altijd component zou zijn. Om dit op te lossen zou
        // component een virtual functie getname ofzo moeten hebben welke in elk component wordt override
    }
    return ++_lowestUnassignedEntityId;
}*/


void EntityManager::removeEntity(int entityId) {
    for (auto &iterator : _componentsByClass) {
        std::string key = iterator.first;
        iterator.second.erase(entityId);
    }
}

bool EntityManager::exists(int entityId) const {
    for (auto &iterator : _componentsByClass) {
        if (iterator.second.find(entityId) != iterator.second.end()) {
            return true;
        }
    }
    return false;
}

std::map<int, std::vector<Component *>> EntityManager::getAllEntitiesWithAllComponents() const {
    std::map<int, std::vector<Component *>> componentsOfEntities;
    //construct map where all components of an entity are grouped
    for (const auto &iterator: _componentsByClass) {
        for (const auto &componentIterator: iterator.second) {
            componentsOfEntities[componentIterator.first].push_back(componentIterator.second.get());
        }
    }
    return componentsOfEntities;
}

/*void EntityManager::accept(GameLevelSerializeVisitor &visitor) {
    visitor.visit(*this);
}

void EntityManager::accept(GameLevelDeserializeVisitor &visitor) {
    visitor.visit(*this);
}*/

/*void EntityManager::accept(SerializationVisitor &visitor) {
    visitor.visit("lowestUnassignedEntityId", _lowestUnassignedEntityId);
    std::map<int, std::vector<Component *>> entitiesWithComponents = getAllEntitiesWithAllComponents();
    for (int i = 0; i <= _lowestUnassignedEntityId; i++) {
        if(auto entityIterator = entitiesWithComponents.find(i); entityIterator != entitiesWithComponents.end()) {
            std::map<std::string, SerializationReceiver*> serializableMap { };
            std::transform(entityIterator->second.begin(), entityIterator->second.end(), serializableMap.begin(), [](Component* component) {
                return std::make_pair(typeid(component).name(), static_cast<SerializationReceiver*>(component));
            });
            visitor.visit("entity" + std::to_string(i), serializableMap);
        }
    }
    for(const auto &entityIterator: getAllEntitiesWithAllComponents()) {
        std::map<std::string, SerializationReceiver*> serializableMap { };
        std::transform(entityIterator.second.begin(), entityIterator.second.end(), serializableMap.begin(), [](Component* component) {
            return std::make_pair(typeid(component).name(), static_cast<SerializationReceiver*>(component));
        });
        visitor.visit("entity", serializableMap);
    }
}

void EntityManager::accept(DeserializationVisitor &visitor) {
    visitor.visit("lowestUnassignedEntityId", _lowestUnassignedEntityId);
    for (int i = 0; i <= _lowestUnassignedEntityId; i++) {
        visitor.visit("entity" + std::to_string(i), )
    }
}*/


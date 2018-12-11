#ifndef PROJECT_SWA_DESERIALIZATIONFACTORY_H
#define PROJECT_SWA_DESERIALIZATIONFACTORY_H

#include <unordered_map>
#include <string>
#include <functional>
#include "SerializationReceiver.h"

class DeserializationFactory {
private:
    std::unordered_map<std::string, std::function<std::unique_ptr<SerializationReceiver>()>> _createFunctions;
    //std::unordered_map<std::string, std::unique_ptr<SerializationReceiver>> _map;
public:
    template<typename T>
    void addType() {
        std::unique_ptr<SerializationReceiver> ptr = std::make_unique<T>();
        _createFunctions[ptr->getName()] = []() {
            return std::make_unique<T>();
        };
        //_map[ptr->getName()] = std::move(ptr);
    }

    void addType(std::unique_ptr<SerializationReceiver> serializationReceiver) {
        //_map[serializationReceiver->getName()] = std::move(serializationReceiver);
    }

    std::unique_ptr<SerializationReceiver> getSerializationReceiver(const std::string &typeName) const {
        const auto &createFunc = _createFunctions.find(typeName);
        if (createFunc != _createFunctions.end())
            return createFunc->second();
        return nullptr;
    }
};

#endif //PROJECT_SWA_DESERIALIZATIONFACTORY_H

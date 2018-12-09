#ifndef PROJECT_SWA_ENTITYMANAGERSERIALIZER_H
#define PROJECT_SWA_ENTITYMANAGERSERIALIZER_H

#include "../GameECS/Entities/EntityManager.h"
#include "../../../TonicEngine/Headers/Storage/XMLSerializationVisitor.h"

class EntityManagerSerializer {
public:
    void serialize(EntityManager &entityManager, XMLSerializationVisitor &visitor);

    void deserialize(EntityManager &entityManager, XMLSerializationVisitor &visitor);
};

void EntityManagerSerializer::serialize(EntityManager &entityManager, XMLSerializationVisitor &visitor) {
    for (const auto &entityIterator: entityManager.getAllEntitiesWithAllComponents()) {
        visitor.createEmbedded("entity");
        for (const auto &componentIterator: entityIterator.second) {
            representationBuilder.createEmbedded(typeid(componentIterator).name());
            componentIterator->represent(representationBuilder);
            representationBuilder.closeEmbedded();
        }
        representationBuilder.closeEmbedded();
        //if(++i > 10) break;
    }

}

#endif //PROJECT_SWA_ENTITYMANAGERSERIALIZER_H

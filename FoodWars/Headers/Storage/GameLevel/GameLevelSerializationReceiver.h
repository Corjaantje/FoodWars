#ifndef PROJECT_SWA_GAMELEVELSERIALIZATIONRECEIVER_H
#define PROJECT_SWA_GAMELEVELSERIALIZATIONRECEIVER_H

#include "../../../../TonicEngine/Headers/Storage/SerializationReceiver.h"
#include "GameLevelSerializeVisitor.h"
#include "GameLevelDeserializeVisitor.h"

class GameLevelSerializationReceiver {
public:
    virtual void accept(GameLevelSerializeVisitor &serializer) const = 0;

    virtual void accept(GameLevelDeserializeVisitor &serializer) = 0;
};

#endif //PROJECT_SWA_GAMELEVELSERIALIZATIONRECEIVER_H

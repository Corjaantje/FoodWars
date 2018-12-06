#ifndef PROJECT_SWA_SERIALIZATIONRECIEVER_H
#define PROJECT_SWA_SERIALIZATIONRECIEVER_H

#include "DeserializeVisitor.h"
#include "SerializationVisitor.h"

class SerializationReceiver {
public:
    virtual void accept(SerializationVisitor &visitor) = 0;
};

#endif //PROJECT_SWA_SERIALIZATIONRECIEVER_H

#ifndef PROJECT_SWA_DESERIALIZEVISITOR_H
#define PROJECT_SWA_DESERIALIZEVISITOR_H

#include <string>

class SerializationReceiver;

class DeserializeVisitor {
public:
    virtual void visit(const std::string &name, std::string &value) = 0; //loadString
    virtual void visit(const std::string &name, int &value) = 0; //loadInt
    virtual void visit(const std::string &name, double &value) = 0; //loadDouble
    virtual void visit(const std::string &name, bool &value) = 0; //loadBoolean
    virtual void visit(const std::string &name, SerializationReceiver &serializationReceiver) = 0;
};

#endif //PROJECT_SWA_DESERIALIZEVISITOR_H

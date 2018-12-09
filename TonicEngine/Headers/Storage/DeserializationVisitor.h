#ifndef PROJECT_SWA_DESERIALIZEVISITOR_H
#define PROJECT_SWA_DESERIALIZEVISITOR_H

#include <string>
#include <memory>
#include "SerializationVisitor.h"

class DeserializationVisitor : public SerializationVisitor {
public:
    void visit(const std::string &name, std::string &value) override = 0;

    void visit(const std::string &name, int &value) override = 0;

    void visit(const std::string &name, double &value) override = 0;

    void visit(const std::string &name, bool &value) override = 0;

    void visit(const std::string &name, SerializationReceiver &receiver) override = 0;

    void visit(const std::string &name, std::vector<SerializationReceiver *> &receivers) override = 0;

    virtual void visit(const std::string &name, std::vector<SerializationReceiver *> &receivers,
                       std::function<SerializationReceiver *()> createFunc) = 0;

};

#endif //PROJECT_SWA_DESERIALIZEVISITOR_H

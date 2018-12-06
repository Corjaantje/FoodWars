#ifndef PROJECT_SWA_VISITOR_H
#define PROJECT_SWA_VISITOR_H

#include <string>

class SerializationReceiver;

class SerializationVisitor {
public:
    virtual void visit(const std::string &name, std::string &value) = 0;

    virtual void visit(const std::string &name, int &value) = 0;

    virtual void visit(const std::string &name, double &value) = 0;

    virtual void visit(const std::string &name, bool &value) = 0;

    virtual void visit(const std::string &name, SerializationReceiver &receiver) = 0;
};

#endif //PROJECT_SWA_VISITOR_H

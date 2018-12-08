#ifndef PROJECT_SWA_VISITOR_H
#define PROJECT_SWA_VISITOR_H

#include <string>
#include <vector>

class SerializationReceiver;

class SerializationVisitor {
public:
    virtual void visit(const std::string &name, std::string &value) = 0;

    virtual void visit(const std::string &name, int &value) = 0;

    virtual void visit(const std::string &name, double &value) = 0;

    virtual void visit(const std::string &name, bool &value) = 0;

    virtual void visit(const std::string &name, SerializationReceiver &receiver) = 0;

    virtual void visit(const std::string &name, std::vector<SerializationReceiver *> &receivers) = 0;

    /*template <typename It>
    void visit(const std::string &name, It& begin, It& end, const std::string &foreachName) {

    };*/
};

#endif //PROJECT_SWA_VISITOR_H

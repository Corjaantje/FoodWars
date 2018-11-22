#ifndef PROJECT_SWA_ISERIALIZABLE_H
#define PROJECT_SWA_ISERIALIZABLE_H

#include <string>
#include <vector>

class ISerializable{
public:
    ISerializable() {

    }
    ~ISerializable() {

    }
    virtual std::vector<std::string> serialize() = 0;
};

#endif //PROJECT_SWA_ISERIALIZABLE_H

#ifndef PROJECT_SWA_BASEPARSER_H
#define PROJECT_SWA_BASEPARSER_H

#include "tinyxml2.h"

template<typename T>
class BaseParser {
public:
    BaseParser(){

    }
    virtual ~BaseParser(){

    }

    virtual T* ParseFromXML(tinyxml2::XMLElement elem) = 0;
};
#endif //PROJECT_SWA_BASEPARSER_H

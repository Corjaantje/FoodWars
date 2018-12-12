//
// Created by pietb on 01-Oct-18.
//

#ifndef PROJECT_SWA_XMLWRITER_H
#define PROJECT_SWA_XMLWRITER_H
#include <vector>
#include "tinyxml2.h"
#include "MyDocument.h"

using namespace tinyxml2;

class XMLWriter {
private:
    XMLDocument xml_doc;
public:
    XMLWriter();
    ~XMLWriter();

    XMLElement *WriteRecursively(const MyNode &node, XMLElement &parent);

    bool WriteXMLFile(const MyDocument &my_doc, const std::string &file_name);

    bool WriteXMLFile(const MyNode &node, const std::string &file_name);
};


#endif //PROJECT_SWA_XMLWRITER_H

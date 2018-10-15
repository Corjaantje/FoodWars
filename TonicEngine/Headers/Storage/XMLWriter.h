//
// Created by pietb on 01-Oct-18.
//

#ifndef PROJECT_SWA_XMLWRITER_H
#define PROJECT_SWA_XMLWRITER_H
#include <vector>
#include "tinyxml2.h"
#include "MyDocument.h"

using namespace tinyxml2;

class XMLWriter
{
private:
    XMLDocument xml_doc;
public:
    XMLWriter();
    ~XMLWriter();

    XMLDocument& WriteXMLFile(MyDocument& my_doc, std::string file_name);
    void WriteRecursively(const MyNode& node, XMLElement& parent);
    //XMLDocument& WriteXMLFile(XMLDocument& doc, std::string file_name);
    //void WriteRecursively(const XMLNode& node, XMLElement& parent);
};


#endif //PROJECT_SWA_XMLWRITER_H

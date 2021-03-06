#include "../../Headers/Storage/XMLReader.h"

#ifndef XMLCheckResult
#define XMLCheckResult(a_eResult) if (a_eResult != XML_SUCCESS) { printf("Error: %i\n", a_eResult); return a_eResult; }
#endif


void XMLReader::ReadRecursively(XMLElement &elem, MyNode &parent) {
    MyNode current_node{elem.Name()};
    const XMLAttribute* xml_attr = elem.FirstAttribute();
    if (xml_attr != nullptr) {
        for (const XMLAttribute *attr = xml_attr; attr; attr = attr->Next()) {
            current_node.AddAttribute(attr->Name(), attr->Value());
        }
    }

    if (elem.GetText() != nullptr) {
        current_node.SetValue(elem.GetText());
    }

    if (elem.FirstChildElement() != nullptr) {// child exists
        ReadRecursively(*elem.FirstChildElement(), current_node);
    }

    if (elem.NextSiblingElement() != nullptr) { // no child, but sibling
        ReadRecursively(*elem.NextSiblingElement(), parent);
    }
    parent.AddChild(current_node);
}

XMLReader::XMLReader() = default;


XMLReader::~XMLReader() = default;

MyDocument XMLReader::LoadFile(const string &file_name) {
    XMLDocument d;
    d.LoadFile(file_name.c_str());
    MyDocument myDocument = ReadXMLFile(d);
    return myDocument;
}

MyDocument XMLReader::ReadXMLFile(XMLDocument &doc) {
    XMLNode* docRoot = doc.FirstChild();
    MyNode rootNode{docRoot->Value()};
    XMLElement *firstElem = docRoot->FirstChildElement();

    ReadRecursively(*firstElem, rootNode);

    return MyDocument{rootNode};
}

std::unique_ptr<MyDocument> XMLReader::LoadFile2(const string &fileName) {
    XMLDocument d;
    d.LoadFile(fileName.c_str());

    XMLNode *docRoot = d.FirstChild();

    if (docRoot != nullptr) {
        MyNode rootNode{docRoot->Value(), nullptr};
        XMLElement *firstElem = docRoot->FirstChildElement();

        ReadRecursively(*firstElem, rootNode);

        auto *myDoc = new MyDocument{rootNode};


        return std::unique_ptr<MyDocument>{myDoc};
    }
    return nullptr;
}

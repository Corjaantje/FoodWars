#include "../../Headers/Storage/XMLWriter.h"

XMLWriter::XMLWriter() = default;


XMLWriter::~XMLWriter() = default;

bool XMLWriter::WriteXMLFile(const MyDocument &doc, const std::string &file_name) {
    XMLElement* root;
    root = xml_doc.NewElement(&doc.GetRoot().GetName()[0]);
    xml_doc.InsertFirstChild(root);
    for (const auto &child : doc.GetRoot().GetChildren()) {
        XMLElement *elem{root};
        WriteRecursively(child, *elem);
    }

    return xml_doc.SaveFile(file_name.c_str()) == 0;
}

bool XMLWriter::WriteXMLFile(const MyNode &node, const std::string &file_name) {
    MyDocument document{node};
    return WriteXMLFile(document, file_name);
}

XMLElement *XMLWriter::WriteRecursively(const MyNode &node, XMLElement &parent) {
    XMLElement *cur_node = xml_doc.NewElement(node.GetName().c_str());

    cur_node->SetName(node.GetName().c_str());
    cur_node->SetText(node.GetValue().c_str());

    if (!node.GetAttributes().empty()) {
        for (auto &attr : node.GetAttributes()) {
            cur_node->SetAttribute(attr.name.c_str(), attr.value.c_str());
        }
    }

    for (auto &kid : node.GetChildren()) { // transcribe each child
        cur_node->InsertEndChild(WriteRecursively(kid, *cur_node));
    }
    parent.InsertEndChild(cur_node);
    return cur_node;
}

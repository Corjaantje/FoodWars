//
// Created by pietb on 01-Oct-18.
//

#include "../../Headers/Storage/XMLWriter.h"
XMLWriter::XMLWriter()
{
}


XMLWriter::~XMLWriter()
{
}

XMLDocument & XMLWriter::WriteXMLFile(MyDocument & doc, std::string file_name)
{
    XMLElement* root;
    MyNode my_root = doc.GetRoot();
    MyNode *current_node = my_root.FirstChildElement();

    const char* root_name = "root";
    root = xml_doc.NewElement(root_name);
    xml_doc.InsertFirstChild(root);

    for (auto &child : my_root.GetChildren())
    {
        XMLElement* elem{ root };
        WriteRecursively(child, *elem);
    }
    xml_doc.SaveFile(file_name.c_str());

    return xml_doc;
    // TODO: insert return statement here
}

void XMLWriter::WriteRecursively(const MyNode & node, XMLElement & parent)
{
    XMLDocument* xml_doc_ptr = &xml_doc;
    XMLElement* cur_node = xml_doc.NewElement(node.GetName().c_str());

    cur_node->SetName(node.GetName().c_str());
    cur_node->SetText(node.GetValue().c_str());

    if (node.GetAttributes().size() > 0)
    {
        for (auto &attr : node.GetAttributes())
        {
            cur_node->SetAttribute(attr.name.c_str(), attr.value.c_str());
        }
    }

    for (auto &kid : node.GetChildren()) // transcribe each child
    {
        WriteRecursively(kid, *cur_node);
    }
    parent.InsertEndChild(cur_node);
}

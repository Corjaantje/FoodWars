//
// Created by pietb on 01-Oct-18.
//

#ifndef PROJECT_SWA_MYNODE_H
#define PROJECT_SWA_MYNODE_H
#include <vector>
#include <string>

using namespace std;
struct Attribute
{
    string name;
    string value;
};

class MyNode
{
public:
    MyNode(string name, MyNode* parent);
    ~MyNode();

    const string GetName() const;
    const vector<MyNode> GetChildren() const;
    const vector<Attribute> GetAttributes() const;
    const string GetValue() const;
    const int GetIntValue() const;
    const MyNode* GetParent() const;

    MyNode& AddChild(MyNode& child);
    Attribute& AddAttribute(Attribute& attribute);

    MyNode* FirstChildElement();
    const MyNode* NextSiblingElement();
    void SetValue(string value);
    void SetParent(MyNode& parent);

    const MyNode& operator=(const MyNode& other);
private:
    string _name;
    vector<MyNode> _children;
    MyNode* _parent;
    vector<Attribute> _attributes;
    string _value;
};


#endif //PROJECT_SWA_MYNODE_H

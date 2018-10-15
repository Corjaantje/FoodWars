//
// Created by pietb on 01-Oct-18.
//

#include "../../Headers/Storage/MyDocument.h"
MyDocument::MyDocument(MyNode& root)
        :_root(root)
{

}

MyDocument::~MyDocument()
{

}

MyNode MyDocument::GetRoot()
{
    return _root;
}

void MyDocument::AddToRoot(MyNode addition)
{
    _root.AddChild(addition);
}

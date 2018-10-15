//
// Created by pietb on 01-Oct-18.
//

#ifndef PROJECT_SWA_MYDOCUMENT_H
#define PROJECT_SWA_MYDOCUMENT_H
#pragma once
#include "MyNode.h"
class MyDocument
{
public:
    MyDocument(MyNode& root);
    ~MyDocument();

    MyNode GetRoot();
    void AddToRoot(MyNode addition);

private:
    MyNode _root;
};


#endif //PROJECT_SWA_MYDOCUMENT_H

//
// Created by pietb on 01-Oct-18.
//

#ifndef PROJECT_SWA_MYDOCUMENT_H
#define PROJECT_SWA_MYDOCUMENT_H
#pragma once
#include "MyNode.h"

class MyDocument {
public:
    explicit MyDocument(const MyNode &root);
    ~MyDocument();

    const MyNode &GetRoot() const;
    void AddToRoot(MyNode addition);

private:
    MyNode _root;
};


#endif //PROJECT_SWA_MYDOCUMENT_H

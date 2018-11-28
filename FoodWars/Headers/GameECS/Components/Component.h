#ifndef PROJECT_SWA_COMPONENTS_H
#define PROJECT_SWA_COMPONENTS_H

class Component {
public:
    Component();
    Component(const Component &other) = delete;
    virtual ~Component();
};

#endif //PROJECT_SWA_COMPONENTS_H
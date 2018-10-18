#ifndef PROJECT_SWA_ISHAPE_H
#define PROJECT_SWA_ISHAPE_H
class Renderlist;
class IShape{
public:
    IShape() = default;
    virtual ~IShape(){};
    virtual void addToRender(Renderlist* renderlist){};
};

#endif //PROJECT_SWA_ISHAPE_H

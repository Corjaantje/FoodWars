#ifndef PROJECT_SWA_ISHAPE_H
#define PROJECT_SWA_ISHAPE_H
class Renderlist;
class IShape{
public:
    int xPos;
    int yPos;
    IShape(int x, int y): xPos(x), yPos(y) {

    }
    virtual ~IShape(){};
    virtual void addToRender(Renderlist* renderlist){};
};

#endif //PROJECT_SWA_ISHAPE_H

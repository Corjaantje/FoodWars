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
    virtual int getWidth() const = 0;
    virtual int getHeight() const = 0;
};

#endif //PROJECT_SWA_ISHAPE_H

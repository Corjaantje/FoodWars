#ifndef PROJECT_SWA_ANIMATIONCOMPONENT_H
#define PROJECT_SWA_ANIMATIONCOMPONENT_H

#include <vector>
#include "Component.h"
#include "../../../../TonicEngine/Headers/Visual/Shapes/IShape.h"

class AnimationComponent : public Component{
public:
    explicit AnimationComponent(std::vector<IShape*> animationShapes, double animationInterval);
    ~AnimationComponent() override;
    double getAnimationInterval() const;
    double getElapsedTime() const;
    int getCurrentShapeIndex() const;
    int getNumberOfAnimationShapes() const;
    IShape* getCurrentShape() const;

    void setAnimationInterval(double animationInterval);
    void setAnimationShapes(std::vector<IShape*> animationShapes);
    void setElapsedTime(double elapsedTime);
    void setCurrentShapeIndex(int currentShapeIndex);
private:
    std::vector<IShape*>  _animationShapes;
    double _animationInterval;
    double _elapsedTime;
    int _currentShapeIndex;
    IShape* _currentShape;
};

#endif //PROJECT_SWA_ANIMATIONCOMPONENT_H
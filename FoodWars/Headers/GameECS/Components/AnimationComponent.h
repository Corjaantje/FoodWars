#ifndef PROJECT_SWA_ANIMATIONCOMPONENT_H
#define PROJECT_SWA_ANIMATIONCOMPONENT_H

#include <vector>
#include <bits/unique_ptr.h>
#include "Component.h"
#include "../../../../TonicEngine/Headers/Visual/Shapes/IShape.h"
#include "DrawableComponent.h"

class AnimationComponent : public Component {
public:
    AnimationComponent();

    explicit AnimationComponent(std::vector<std::unique_ptr<IShape>> animationShapes, double animationInterval);

    ~AnimationComponent() override;
    double getAnimationInterval() const;
    double getElapsedTime() const;
    int getCurrentShapeIndex() const;
    int getNumberOfAnimationShapes() const;
    IShape* getCurrentShape() const;
    bool getIsLookingLeft()const;
    bool getIsIdle()const;

    void setAnimationInterval(double animationInterval);

    void setAnimationShapes(std::vector<std::unique_ptr<IShape>> animationShapes);
    void setElapsedTime(double elapsedTime);
    void setCurrentShapeIndex(int currentShapeIndex);
    void setIsLookingLeft(bool isLookingLeft);
    void setIsIdle(bool isIdle);

    void accept(SerializationVisitor &visitor) override;

    std::string getName() const override;

private:
    std::vector<std::unique_ptr<IShape>> _animationShapes;
    bool _isLookingLeft;
    bool _isIdle;
    double _animationInterval;
    double _elapsedTime;
    int _currentShapeIndex;
    IShape* _currentShape;
};

#endif //PROJECT_SWA_ANIMATIONCOMPONENT_H
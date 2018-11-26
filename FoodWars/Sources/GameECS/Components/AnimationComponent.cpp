#include <utility>
#include "../../../Headers/GameECS/Components/AnimationComponent.h"

AnimationComponent::AnimationComponent() : AnimationComponent({}, 1) {

}

AnimationComponent::AnimationComponent(std::vector<IShape *> animationShapes, double animationInterval)
        : _animationShapes(std::move(animationShapes)), _animationInterval(animationInterval), _elapsedTime(0),
          _isIdle(false), _isLookingLeft(false) {
    setCurrentShapeIndex(0);
}

AnimationComponent::~AnimationComponent() {
    /*for(IShape* shape:_animationShapes)
    {
        delete shape;
    }*/
}

double AnimationComponent::getAnimationInterval() const {
    return _animationInterval;
}

double AnimationComponent::getElapsedTime() const {
    return _elapsedTime;
}

int AnimationComponent::getCurrentShapeIndex() const {
    return _currentShapeIndex;
}

int AnimationComponent::getNumberOfAnimationShapes() const {
    return _animationShapes.size();
}

void AnimationComponent::setAnimationShapes(std::vector<IShape*> animationShapes) {
    for(IShape* shape:_animationShapes)
    {
        delete shape;
    }
    _animationShapes = std::move(animationShapes);
    _elapsedTime = 0;
    setCurrentShapeIndex(0);
}

void AnimationComponent::setAnimationInterval(double animationInterval) {
    _animationInterval = animationInterval;
}

void AnimationComponent::setElapsedTime(double elapsedTime) {
    _elapsedTime = elapsedTime;
}

void AnimationComponent::setCurrentShapeIndex(int currentShapeIndex) {
    _currentShapeIndex = currentShapeIndex;
    _currentShape = _animationShapes[currentShapeIndex];
}

IShape *AnimationComponent::getCurrentShape() const {
    return _currentShape;
}

void AnimationComponent::setIsLookingLeft(bool isLookingLeft) {
    _isLookingLeft = isLookingLeft;
}

bool AnimationComponent::getIsLookingLeft() const {
    return _isLookingLeft;
}

bool AnimationComponent::getIsIdle() const {
    return _isIdle;
}

void AnimationComponent::setIsIdle(bool isIdle) {
    _isIdle = isIdle;
}

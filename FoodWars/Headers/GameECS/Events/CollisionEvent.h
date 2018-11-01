#ifndef PROJECT_SWA_COLLISIONEVENT_H
#define PROJECT_SWA_COLLISIONEVENT_H

enum class Direction {
    Left,
    Right,
    Top,
    Bottom
};

class CollisionEvent {
private:
    int entity; // the moving component
    Direction entityDirection; // direction of the entity which collides
    int otherEntity; // the entityid with which the moving component collides
    Direction otherEntityDirection; // direction of the other entity which collides
public:
    CollisionEvent(int entity, Direction entityDirection, int otherEntity, Direction otherEntityDirection);
    int getEntity() const;
    int getOtherEntity() const;
    Direction getEntityDirection() const;
    Direction getOtherEntityDirection() const;
};

#endif //PROJECT_SWA_COLLISIONEVENT_H

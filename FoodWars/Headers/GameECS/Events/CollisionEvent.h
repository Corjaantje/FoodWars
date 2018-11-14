#ifndef PROJECT_SWA_COLLISIONEVENT_H
#define PROJECT_SWA_COLLISIONEVENT_H

class CollisionEvent {
private:
    int entity; // the moving component
    int otherEntity; // the entityid with which the moving component collides
    double collisionAngle; // the angle of which the other enity is hit. 0 = top, 90 = left etc.
public:
    CollisionEvent(int entity, int otherEntity, double collisionAngle);
    int getEntity() const;
    int getOtherEntity() const;
    double getCollisionAngle() const;
};

#endif //PROJECT_SWA_COLLISIONEVENT_H

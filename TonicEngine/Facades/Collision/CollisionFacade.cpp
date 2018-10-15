#include "../../Headers/Collision/CollisionFacade.h"
#include <cmath>
#include <math.h>

bool CollisionFacade::detectCollision(Shape* shapeA, Shape* shapeB, Vector2D movement)
{
   Rectangle* recA = dynamic_cast<Rectangle*>(shapeA);
   Rectangle* recB = dynamic_cast<Rectangle*>(shapeB);
   Circle* cirA = dynamic_cast<Circle*>(shapeA);
   Circle* cirB = dynamic_cast<Circle*>(shapeA);

    // rectangle - rectangle collision
    if (recA  && recB)
    {
        recA->position += movement;
       return detectCollision(recA, recB);
    }
    // circle - circle collision
    if (cirA && cirB)
    {
        cirA->position += movement;
        return detectCollision(cirA, cirB);
    }
    // circle - rectangle collision
    if (cirA && recB)
    {
        cirA->position += movement;
        return detectCollision(cirA, recB);
    }
    if (recA && cirB)
    {
        recA->position += movement;
        return detectCollision(cirB, recA);
    }
}

bool CollisionFacade::detectCollision(Circle* cirA, Rectangle* recB)
{
    float circleDistanceX = abs(cirA->position.x - recB->position.x);
    float circleDistanceY = abs(cirA->position.y - recB->position.y);

    if (circleDistanceX > (recB->width/2 + cirA->radius)) { return false; }
    if (circleDistanceY > (recB->height/2 + cirA->radius)) { return false; }

    if (circleDistanceX <= (recB->width/2)) { return true; }
    if (circleDistanceY <= (recB->height/2)) { return true; }

    float cornerDistanceSq = pow(circleDistanceX - recB->width/2, 2) +
                             pow(circleDistanceY - recB->height/2, 2);

    return (cornerDistanceSq <= (pow(cirA->radius, 2)));
}

bool CollisionFacade::detectCollision(Circle *cirA, Circle *cirB)
{
    return abs((cirA->position.x - cirB->position.x) * (cirA->position.x - cirB->position.x) +
               (cirA->position.y - cirB->position.y) * (cirA->position.y - cirB->position.y)) <
           (cirA->radius + cirB->radius) * (cirA->radius + cirB->radius);
}

bool CollisionFacade::detectCollision(Rectangle *recA, Rectangle *recB)
{
    if (
            recA->position.x + recA->width >= recA->position.x &&
            recB->position.x + recB->width >= recA->position.x &&
            recA->position.y + recA->height >= recB->position.y &&
            recB->position.y + recB->height >= recA->position.y
            )
    {
        return true;
    }
    return false;
}
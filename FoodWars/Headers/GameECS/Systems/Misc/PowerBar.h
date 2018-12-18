#ifndef PROJECT_SWA_POWERBAR_H
#define PROJECT_SWA_POWERBAR_H

#include "../../Entities/EntityManager.h"
#include "../../Components/PositionComponent.h"
#include "../../Components/Collider/BoxCollider.h"
#include "../../../../../TonicEngine/Headers/Visual/Shapes/ShapeRectangle.h"

class PowerBar {
private:
    EntityManager *_entityManager;
    PositionComponent *_playerPosition;
    BoxCollider *_playerCollider;
    ShapeRectangle *_powerBarRect;

    int _playerId;
    int _power;
    double _timePassed;
    int _powerBarBackground;
    int _powerBar;
    bool _risingPower;
    bool _locked;
public:
    explicit PowerBar(EntityManager &entityManager);

    ~PowerBar();

    void update(double dt);

    void lockToPlayer(int playerId);

    void show();

    void hide();

    void lock();

    void unlock();

    int getPower() const;

    void setPower(int power);

    bool isVisible() const;
};

#endif //PROJECT_SWA_POWERBAR_H

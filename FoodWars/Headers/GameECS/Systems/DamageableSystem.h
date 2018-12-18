#ifndef PROJECT_SWA_DAMAGEABLESYSTEM_H
#define PROJECT_SWA_DAMAGEABLESYSTEM_H

#include "IBaseSystem.h"
#include "../Components/DamageableComponent.h"
#include "../Events/CollisionEventHandler.h"
#include "../../../../TonicEngine/Headers/Audio/AudioFacade.h"
#include "../../DamageCalculator.h"
#include "../Components/DrawableComponent.h"
#include "../../../../TonicEngine/Headers/Visual/Shapes/ShapeSprite.h"
#include "../Components/PositionComponent.h"
#include "../Components/Collider/BoxCollider.h"

class SplashDamage {
private:
    int _entityId;
    int _playerId;
    int _width;
    int _height;
    double _elapsedTime;
    EntityManager *_entityManager;
    PositionComponent *_playerPosition;
    BoxCollider *_playerCollider;
public:
    explicit SplashDamage(EntityManager &entityManager, int playerId) : _entityId{entityManager.createEntity()},
                                                                        _playerId{playerId}, _width{32}, _height{32},
                                                                        _elapsedTime{0}, _entityManager{&entityManager},
                                                                        _playerPosition{
                                                                                _entityManager->getComponentFromEntity<PositionComponent>(
                                                                                        _playerId)}, _playerCollider{
                    _entityManager->getComponentFromEntity<BoxCollider>(_playerId)} {
        _entityManager->addComponentToEntity<DrawableComponent>(_entityId,
                                                                std::make_unique<ShapeSprite>(_width, _height, 0, 0,
                                                                                              "SplashDamage.png", 3));
        _entityManager->addComponentToEntity<PositionComponent>(_entityId,
                                                                _playerPosition->X + _playerCollider->width / 2.0 -
                                                                _width / 2.0,
                                                                _playerPosition->Y + _playerCollider->height / 2.0 -
                                                                _height / 2.0);
    }

    ~SplashDamage() {
        hide();
    }

    double getElapsedTime() const {
        return _elapsedTime;
    }

    double increaseTime(double dt) {
        _elapsedTime += dt;
    }

    void hide() {
        if (_entityId > 0) {
            _entityManager->removeEntity(_entityId);
            _entityId = -1;
        }
    }
};

class DamageableSystem : public IBaseSystem, CollisionEventHandler {
private:
    EntityManager *_entityManager;
    AudioFacade* _audioFacade;
    DamageCalculator _damageCalculator;
    std::vector<SplashDamage> _splashDamages;
public:
    DamageableSystem(EntityManager &entityManager, AudioFacade& audioFacade, IObservable<CollisionEvent> &collisionEventObservable);
    ~DamageableSystem() override;

    bool canHandle(const CollisionEvent& collisionEvent) override;
    void handleCollisionEvent(const CollisionEvent& collisionEvent) override {};
    void handleCollisionEvent(int projectileId, int targetId);
    void update(double deltaTime) override;

};

#endif //PROJECT_SWA_DAMAGEABLESYSTEM_H

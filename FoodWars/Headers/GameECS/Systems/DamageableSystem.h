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
#include "../Components/AnimationComponent.h"

class SplashDamage {
private:
    unsigned int amountOfSprites = 6;
    double animationInterval = 0.2;

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

        double x = _playerPosition->X + _playerCollider->width / 2.0 -
                   _width / 2.0;

        double y =  _playerPosition->Y + _playerCollider->height / 2.0 -
                    _height / 2.0;
        _entityManager->addComponentToEntity<DrawableComponent>(_entityId,
                                                                std::make_unique<ShapeSprite>(_width, _height, x, y, "SplashDamage3.png", 2));

        std::vector<std::unique_ptr<IShape>> animationShapes{amountOfSprites};
        for(int i = 1; i <= amountOfSprites; i++) {
            animationShapes[i - 1]  = std::make_unique<ShapeSprite>(_width, _height, x, y, "SplashDamage" + std::to_string(i) + ".png", 3);
        }
        _entityManager->addComponentToEntity<AnimationComponent>(_entityId, std::move(animationShapes), animationInterval);
        _entityManager->addComponentToEntity<PositionComponent>(_entityId, x, y );
    }

    ~SplashDamage() {
        hide();
    }

    bool remove() const {
        return _elapsedTime >= amountOfSprites * animationInterval;
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

#include "../../../Headers/GameECS/Systems/ShootSystem.h"
#include "../../../Headers/GameECS/Components/TurnComponent.h"
#include "../../../Headers/GameECS/Components/Collider/BoxCollider.h"
#include "../../../Headers/GameECS/Components/GravityComponent.h"
#include "../../../Headers/GameECS/Components/DamageableComponent.h"
#include "../../../Headers/GameECS/Components/DamagingComponent.h"
#include "../../../Headers/GameECS/Components/DrawableComponent.h"
#include <math.h>


ShootSystem::ShootSystem(std::shared_ptr<EntityManager> entityManager,
                            std::shared_ptr<VisualFacade> visualFacade,
                                std::shared_ptr<InputFacade> inputFacade) :
                                                _entityManager{std::move(entityManager)},
                                                _visualFacade{std::move(visualFacade)},
                                                _isShooting{false},
                                                _projectileFired{false},
                                                _projectile{0},
                                                _projectileAcceleration{10}
{
    inputFacade->getMouseEventObservable()->registerObserver(this);
}

ShootSystem::~ShootSystem() = default;

void ShootSystem::update(double deltaTime) {
    if (!_entityManager->exists(_projectile)) _projectileFired = false;
    if(_projectileFired)
    {

        auto projectilePos = _entityManager->getComponentFromEntity<PositionComponent>(_projectile);
        auto projectileSize = _entityManager->getComponentFromEntity<BoxCollider>(_projectile);
        auto projectileMove = _entityManager->getComponentFromEntity<MoveComponent>(_projectile);

        if ((projectilePos->X + projectileSize->width) >= 1590 || projectilePos->X <= 1 ||
            projectilePos->Y <= 1 || (projectilePos->Y + projectileSize->height) >= 890) {
            _projectileFired = false;
            _entityManager->removeEntity(_projectile);
        }
        double accelerationChange = _projectileAcceleration * deltaTime;
        projectileMove->yVelocity -= accelerationChange;
        _projectileAcceleration -= accelerationChange;

    }
}

void ShootSystem::update(std::shared_ptr<MouseEvent> event) {
    while(_isShooting && !_projectileFired)
    {
        int currentPlayer = 0;
        auto turnComponents = _entityManager->getAllEntitiesWithComponent<TurnComponent>();
        for (auto const &x : turnComponents)
        {
            if (x.second->isMyTurn()) {
                currentPlayer = x.first;
                break;
            }
        }
        auto currentPlayerPos = _entityManager->getComponentFromEntity<PositionComponent>(currentPlayer);
        if (event->getMouseEventType() == MouseEventType::Down && event->getMouseClickType() == MouseClickType::Left) {
            std::cout << "xPlayer: " << currentPlayerPos->X << " xMouse: " << event->getXPosition() << std::endl;
            std::cout << "yPlayer: " << currentPlayerPos->Y << " yMouse: " << event->getYPosition() << std::endl;
            double distance = hypot(event->getXPosition() - currentPlayerPos->X, currentPlayerPos->Y - event->getYPosition());

            double radius = acos((event->getXPosition() - currentPlayerPos->X) / distance);
            double angle = radius *(180/M_PI);
//            double vectorX = cos(angle);
//            double vectorY = sin(angle);

            auto playerSize = _entityManager->getComponentFromEntity<BoxCollider>(currentPlayer);
            double angleX = event->getXPosition() - (currentPlayerPos->X);
            double angleY = event->getYPosition() - (currentPlayerPos->Y);
            std::cout << "V: " << angleY << std::endl;
            std::cout << "maxV: " << angleY * sin(radius)*angleY * sin(radius)/2*9.81 << std::endl;
            generateProjectile(currentPlayerPos, angleX, angleY);
            _isShooting = false;
            _projectileFired = true;

            for(const auto &iterator: turnComponents) {
                if(iterator.second->isMyTurn()) {
                    iterator.second->switchTurn(false);
                    for(const auto& it2: turnComponents) {
                        if(it2.first != iterator.first) {
                            it2.second->switchTurn(true);
                            it2.second->setRemainingTime(30.0);
                            break;
                        }
                    }
                    break;
                }
            }
        }
    }
}

void ShootSystem::toggleShooting() {
    _isShooting = !_isShooting;
}

void ShootSystem::generateProjectile(std::shared_ptr<PositionComponent> pos, double velocityX, double velocityY) {
    _projectile = _entityManager->createEntity();

    int posX = pos->X + static_cast<int>(velocityX / 4);
    int posY = pos->Y + static_cast<int>(velocityY / 4);

    auto drawableComponent = new DrawableComponent;
    drawableComponent->shape = std::make_unique<ShapeSprite>(ShapeSprite(11, 38, posX, posY, "carrot.png"));

    _entityManager->addComponentToEntity(_projectile, drawableComponent);
    _entityManager->addComponentToEntity(_projectile, new PositionComponent(posX, posY));
    _entityManager->addComponentToEntity(_projectile, new BoxCollider(20, 20));
    _entityManager->addComponentToEntity(_projectile, new DamagingComponent());

    auto moveComponent = new MoveComponent();
    moveComponent->xVelocity = velocityX / 2;
    moveComponent->yVelocity = velocityY / 2;
    _entityManager->addComponentToEntity(_projectile, moveComponent);
}
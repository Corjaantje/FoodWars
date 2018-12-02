#include "../../../Headers/GameECS/Systems/ShootingSystem.h"
#include "../../../Headers/GameECS/Components/TurnComponent.h"
#include "../../../Headers/GameECS/Components/DamageableComponent.h"
#include "../../../Headers/GameECS/Components/DrawableComponent.h"
#include "../../../../TonicEngine/Headers/Visual/Shapes/ShapeLine.h"
#include "../../../Headers/GameECS/Components/DamagingComponent.h"
#include "../../../Headers/GameECS/Components/GravityComponent.h"

ShootingSystem::ShootingSystem(EntityManager &entityManager,
                               AudioFacade& audioFacade,
                               VisualFacade& visualFacade,
                               InputFacade& inputFacade) :
        _audioFacade(&audioFacade),
        _entityManager{&entityManager},
        _visualFacade{&visualFacade},
        _isShooting{false},
        _projectileFired{false},
        _projectile{0} 
{
    inputFacade.getMouseEventObservable().registerObserver(this);
}

void ShootingSystem::update(double deltaTime) {
    if (!_entityManager->exists(_projectile)) _projectileFired = false;
    if (_projectileFired) {
        auto projectilePos = _entityManager->getComponentFromEntity<PositionComponent>(_projectile);
        auto projectileSize = _entityManager->getComponentFromEntity<BoxCollider>(_projectile);
        auto projectileMove = _entityManager->getComponentFromEntity<MoveComponent>(_projectile);

        if ((projectilePos->X + projectileSize->width) >= 1590 || projectilePos->X <= 1
            || (projectilePos->Y + projectileSize->height) >= 890) {
            _projectileFired = false;
            _entityManager->removeEntity(_projectile);
        }
    }
}

void ShootingSystem::update(const MouseEvent& event) {
    if(_isShooting && !_projectileFired)
    {
        int currentPlayer = 0;
        auto turnComponents = _entityManager->getAllEntitiesWithComponent<TurnComponent>();
        for (auto const &x : turnComponents) {
            if (x.second->isMyTurn()) {
                currentPlayer = x.first;
                break;
            }
        }
        auto currentPlayerPos = _entityManager->getComponentFromEntity<PositionComponent>(currentPlayer);
        auto playerSize = _entityManager->getComponentFromEntity<BoxCollider>(currentPlayer);
        int playerCenterX = currentPlayerPos->X + playerSize->width / 2.0;
        int playerCenterY = currentPlayerPos->Y + playerSize->height / 2.0;
        double deltaX = event.getXPosition() - playerCenterX;
        double deltaY = event.getYPosition() - playerCenterY;
        if (deltaX > 250) deltaX = 250;
        else if (deltaX < -250) deltaX = -250;
        if (deltaY > 250) deltaY = 250;
        else if (deltaY < -250) deltaY = -250;
        double toX = playerCenterX + deltaX;
        double toY = playerCenterY + deltaY;

        if (event.getMouseEventType() == MouseEventType::Down && event.getMouseClickType() == MouseClickType::Left) {
            createShootingLine(playerCenterX, playerCenterY, toX, toY);
        }

        if (event.getMouseEventType() == MouseEventType::Drag) {
            if (!_entityManager->exists(_shootingLine)) createShootingLine(playerCenterX, playerCenterY, toX, toY);
            auto drawable = _entityManager->getComponentFromEntity<DrawableComponent>(_shootingLine);
            auto line = static_cast<ShapeLine *>(drawable->getShape());
            line->xPos = playerCenterX;
            line->yPos = playerCenterY;
            line->xPos2 = toX;
            line->yPos2 = toY;
        }

        if (event.getMouseEventType() == MouseEventType::Up && event.getMouseClickType() == MouseClickType::Left) {
            generateProjectile(*currentPlayerPos, *playerSize, deltaX, deltaY);
            _isShooting = false;
            _projectileFired = true;
            _entityManager->removeEntity(_shootingLine);
            _entityManager->getComponentFromEntity<TurnComponent>(currentPlayer)->lowerEnergy(20);
            _audioFacade->playEffect("jump");
        }
    }
}

void ShootingSystem::createShootingLine(int fromX, int fromY, int toX, int toY) {
    _shootingLine = _entityManager->createEntity();
    _entityManager->addComponentToEntity<DrawableComponent>(_shootingLine,
                                                            std::make_unique<ShapeLine>(fromX, fromY, toX, toY,
                                                                                        Colour(0, 0, 0, 0)));
}

void ShootingSystem::toggleShooting() {
    if (!_projectileFired)
        _isShooting = !_isShooting;
}

void
ShootingSystem::generateProjectile(const PositionComponent &playerPositionComponent, const BoxCollider &playerCollider,
                                   double velocityX, double velocityY) {
    _projectile = _entityManager->createEntity();
    int projectileWidth = 11;
    int projectileHeight = 32;
    int posX = playerPositionComponent.X;
    int posY = playerPositionComponent.Y;
    if (velocityX > 0) posX += projectileWidth + playerCollider.width + 1;
    else posX -= projectileWidth + 1;
    if (velocityY < 0) posY -= projectileHeight + 1;

    const double speedModifier = 2.5;
    _entityManager->addComponentToEntity<DrawableComponent>(_projectile, std::make_unique<ShapeSprite>(projectileWidth,
                                                                                                       projectileHeight,
                                                                                                       posX, posY,
                                                                                                       "carrot.png"));
    _entityManager->addComponentToEntity<PositionComponent>(_projectile, posX, posY);
    _entityManager->addComponentToEntity<BoxCollider>(_projectile, projectileWidth, projectileHeight);
    _entityManager->addComponentToEntity<DamagingComponent>(_projectile, 25);
    _entityManager->addComponentToEntity<DamageableComponent>(_projectile, 10);
    _entityManager->addComponentToEntity<GravityComponent>(_projectile, 6.5 * speedModifier);
    _entityManager->addComponentToEntity<MoveComponent>(_projectile, velocityX * speedModifier,
                                                        velocityY * speedModifier);
}
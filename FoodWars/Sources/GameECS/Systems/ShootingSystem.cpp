#include <unistd.h>
#include "../../../Headers/GameECS/Systems/ShootingSystem.h"
#include "../../../Headers/GameECS/Components/TurnComponent.h"
#include "../../../Headers/GameECS/Components/DamageableComponent.h"
#include "../../../Headers/GameECS/Components/DrawableComponent.h"
#include "../../../../TonicEngine/Headers/Visual/Shapes/ShapeLine.h"
#include <cmath>
#include "../../../Headers/GameECS/Components/DamagingComponent.h"
#include "../../../Headers/GameECS/Components/GravityComponent.h"
#include "../../../Headers/GameECS/Components/PlayerComponent.h"


ShootingSystem::ShootingSystem(EntityManager &entityManager,
                               AudioFacade& audioFacade,
                               VisualFacade& visualFacade,
                               InputFacade& inputFacade) :
        _audioFacade(&audioFacade),
        _entityManager{&entityManager},
        _visualFacade{&visualFacade},
        _projectileFired{false},
        _projectile{-1},
        _timePassed{0},
        _mouseDown{false},
        _powerBarX(0),
        _powerBarY(0),
        _power(0),
        _risingPower(true),
        _currentPlayer(0),
        _otherPlayer(0),
        _powerBarBackground(-1),
        _powerBar(-1),
        _shootingLine(-1)

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
    _timePassed += deltaTime;

    if (_mouseDown) {
        if(_timePassed >= 0.02) {
            powerHandler();

            _timePassed = 0;
        }
    }
}

void ShootingSystem::update(const MouseEvent& event) {
    if(!_projectileFired) {
        setPlayerTurn();
        if (!_entityManager->getComponentFromEntity<TurnComponent>(_otherPlayer)->getIsShooting() &&
            _entityManager->getComponentFromEntity<TurnComponent>(_currentPlayer)->getIsShooting()) {

            Weapon *selectedWeapon = _entityManager->getComponentFromEntity<PlayerComponent>(
                    _currentPlayer)->getSelectedWeapon();

            if (_entityManager->getComponentFromEntity<TurnComponent>(_currentPlayer)->getEnergy() >= 20 &&
                selectedWeapon->getAmmo() > 0) {

                auto currentPlayerPos = _entityManager->getComponentFromEntity<PositionComponent>(_currentPlayer);
                auto playerSize = _entityManager->getComponentFromEntity<BoxCollider>(_currentPlayer);
                int playerCenterX = currentPlayerPos->X + playerSize->width / 2.0;
                int playerCenterY = currentPlayerPos->Y + playerSize->height / 2.0;

                // Check if player is looking left or right to determine the x position of the powerbar
                if (!_entityManager->getComponentFromEntity<AnimationComponent>(_currentPlayer)->getIsLookingLeft())
                    _powerBarX = playerCenterX - 55;
                else
                    _powerBarX = playerCenterX + 35;
                _powerBarY = playerCenterY - 25;

                double deltaX = event.getXPosition() - playerCenterX;
                double deltaY = event.getYPosition() - playerCenterY;

                // shooting in a circle
                double totalLength = sqrt(deltaX * deltaX + deltaY * deltaY);
                double length = totalLength > 150 ? 150 : totalLength;
                double scale = length / totalLength;

                deltaX *= scale;
                deltaY *= scale;

                double toX = playerCenterX + deltaX;
                double toY = playerCenterY + deltaY;

                if (event.getMouseEventType() == MouseEventType::Down &&
                    event.getMouseClickType() == MouseClickType::Left) {

                    createShootingLine(playerCenterX, playerCenterY, toX, toY);
                    createPowerBar();
                    _powerBar = _entityManager->createEntity();
                    _mouseDown = true;
                }

                if (event.getMouseEventType() == MouseEventType::Drag) {
                    if (!_entityManager->exists(_shootingLine))
                        createShootingLine(playerCenterX, playerCenterY, toX, toY);
                    auto drawable = _entityManager->getComponentFromEntity<DrawableComponent>(_shootingLine);
                    auto line = static_cast<ShapeLine *>(drawable->getShape());
                    line->xPos = playerCenterX;
                    line->yPos = playerCenterY;
                    line->xPos2 = toX;
                    line->yPos2 = toY;
                }

                if (event.getMouseEventType() == MouseEventType::Up &&
                    event.getMouseClickType() == MouseClickType::Left) {
                    generateProjectile(*currentPlayerPos, *playerSize, deltaX, deltaY, selectedWeapon, playerCenterX, playerCenterY);
                    _projectileFired = true;
                    _entityManager->getComponentFromEntity<TurnComponent>(_currentPlayer)->lowerEnergy(20);
                    _audioFacade->playEffect("throwing");
                    resetShooting();
                }
            } else {
                if (event.getMouseEventType() == MouseEventType::Down &&
                    event.getMouseClickType() == MouseClickType::Left) {
                    _audioFacade->playEffect("negative");
                }
            }
        } else {
            resetShooting();
        }
    }
}

void ShootingSystem::createShootingLine(int fromX, int fromY, int toX, int toY) {
    _shootingLine = _entityManager->createEntity();
    _entityManager->addComponentToEntity<DrawableComponent>(_shootingLine,
                                                            std::make_unique<ShapeLine>(fromX, fromY, toX, toY,
                                                                                        Colour(0, 0, 0, 0)));
}

void ShootingSystem::createPowerBar() {
    _powerBarBackground = _entityManager->createEntity();
    _entityManager->addComponentToEntity<DrawableComponent>(_powerBarBackground,
                                                            std::make_unique<ShapeRectangle>(20, 50, _powerBarX, _powerBarY,
                                                                    Colour(0, 0, 0, 0)));
}

void ShootingSystem::powerHandler() {
    int width = 16;
    int height = _power * -1;
    int xPos = _powerBarX + 2;
    int yPos = _powerBarY + 50;

    if (!_risingPower) {
        if (_power > 0) {
            _entityManager->addComponentToEntity<DrawableComponent>(_powerBar,
                                                                    std::make_unique<ShapeRectangle>(width, height, xPos, yPos, Colour(255, 0, 0, 0)));
            _power--;
        } else {
            _risingPower = true;
        }
    } else {
        if (_power < 50) {
            _entityManager->addComponentToEntity<DrawableComponent>(_powerBar,
                                                                    std::make_unique<ShapeRectangle>(width, height, xPos, yPos, Colour(255, 0, 0, 0)));
            _power++;
        } else {
            _risingPower = false;
        }
    }

}

void ShootingSystem::toggleShooting() {
    if (!_projectileFired) {
        setPlayerTurn();
        auto playerTurn = _entityManager->getComponentFromEntity<TurnComponent>(_currentPlayer);
        if (playerTurn != nullptr && _entityManager->getComponentFromEntity<PlayerComponent>(_currentPlayer)->getSelectedWeaponAvailability() > 0) {
            playerTurn->changeIsShooting();
            if (!playerTurn->getIsShooting())
                resetShooting();
            else
                _entityManager->getComponentFromEntity<MoveComponent>(_currentPlayer)->xVelocity = 0;
        }
    }
}

void ShootingSystem::resetShooting() {
    _mouseDown = false;
    _power = 0;
    _entityManager->removeEntity(_powerBarBackground);
    _entityManager->removeEntity(_powerBar);
    _entityManager->removeEntity(_shootingLine);
    _entityManager->getComponentFromEntity<TurnComponent>(_currentPlayer)->setIsShooting(false);
}

void ShootingSystem::setPlayerTurn() {
    auto turnComponents = _entityManager->getAllEntitiesWithComponent<TurnComponent>();
    for (auto const &x : turnComponents) {
        if (x.second->isMyTurn()) {
            _currentPlayer = x.first;
            break;
        }
    }
    for(const auto &iterator : _entityManager->getAllEntitiesWithComponent<PlayerComponent>()){
        if (iterator.first != _currentPlayer) {
            _otherPlayer = iterator.first;
            _entityManager->getComponentFromEntity<TurnComponent>(_otherPlayer)->setIsShooting(false);
            break;
        }
    }
}

void ShootingSystem::generateProjectile(const PositionComponent &playerPositionComponent, const BoxCollider &playerCollider,
                                double velocityX, double velocityY, Weapon* selectedWeapon, int playerCenterX, int playerCenterY) {
    _projectile = _entityManager->createEntity();
    int projectileWidth = 11;
    int projectileHeight = 32;
    int posX = playerCenterX;
    int posY = playerCenterY;
    // Checks for shooting down
    if (velocityX > 0 && velocityY > 70) posY = playerCenterY + (playerCollider.height / 2) + 1;
    else if (velocityX <= 0 && velocityY > 70) posY = playerCenterY + (playerCollider.height / 2) + 1;
        // Checks for shooting up
    else if (velocityX > 0 && velocityY <= -70) posY = playerCenterY - (playerCollider.height / 2) - 1;
    else if (velocityX <= 0 && velocityY <= -70) posY = playerCenterY - (playerCollider.height / 2) - 1;
        // Remaining default checks
    else if (velocityX > 0) posX = playerCenterX + (playerCollider.width / 2) + 1;
    else if (velocityX <= 0) posX = playerCenterX - (playerCollider.width / 2) - (projectileWidth - 1);
    if (velocityY < 0) posY -= projectileHeight + 1;

    const double speedModifier = 2.5;

    _entityManager->addComponentToEntity<DrawableComponent>(_projectile, std::make_unique<ShapeSprite>(projectileWidth,
                                                                                                       projectileHeight,
                                                                                                       posX, posY,
                                                                                                       selectedWeapon->getImage()));
    _entityManager->addComponentToEntity<PositionComponent>(_projectile, posX, posY);
    _entityManager->addComponentToEntity<BoxCollider>(_projectile, projectileWidth, projectileHeight);
    _entityManager->addComponentToEntity<DamagingComponent>(_projectile, 25, selectedWeapon->getFaction());
    _entityManager->addComponentToEntity<DamageableComponent>(_projectile, 10);
    _entityManager->addComponentToEntity<GravityComponent>(_projectile, 6 * speedModifier);
    _entityManager->addComponentToEntity<MoveComponent>(_projectile, (_power / 20) * velocityX * speedModifier,
                                                        (_power / 20) * velocityY * speedModifier);
    selectedWeapon->lowerAmmo();
    _power = 0;
}
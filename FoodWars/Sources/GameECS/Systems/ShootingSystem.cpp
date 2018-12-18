#include <cmath>
#include "../../../Headers/GameECS/Systems/ShootingSystem.h"
#include "../../../Headers/GameECS/Components/TurnComponent.h"
#include "../../../../TonicEngine/Headers/Visual/Shapes/ShapeLine.h"
#include "../../../Headers/GameECS/Components/PlayerComponent.h"


ShootingSystem::ShootingSystem(EntityManager &entityManager,
                               AudioFacade& audioFacade,
                               VisualFacade& visualFacade,
                               InputFacade& inputFacade) :
        _shootingLine{entityManager},
        _audioFacade(&audioFacade),
        _entityManager{&entityManager},
        _visualFacade{&visualFacade},
        _projectileBuilder{entityManager},
        _projectileFired{false},
        _projectile{-1},
        _mouseDown{false},
        _currentPlayer(0),
        _otherPlayer(0),
        _powerBar(entityManager) {
    inputFacade.getMouseEventObservable().registerObserver(this);
}

void ShootingSystem::update(double deltaTime) {
    if (!_entityManager->exists(_projectile)) _projectileFired = false;
    if (_projectileFired) {
        auto projectilePos = _entityManager->getComponentFromEntity<PositionComponent>(_projectile);
        auto projectileSize = _entityManager->getComponentFromEntity<BoxCollider>(_projectile);

        if ((projectilePos->X + projectileSize->width) >= 1590 || projectilePos->X <= 1
            || (projectilePos->Y + projectileSize->height) >= 890) {
            _projectileFired = false;
            _entityManager->removeEntity(_projectile);
        }
    }

    if (_mouseDown && _powerBar.isVisible()) {
        _powerBar.update(deltaTime);
    }
}

void ShootingSystem::update(const MouseEvent& event) {
    if(!_projectileFired) {
        setPlayerTurn();
        if (!_entityManager->getComponentFromEntity<TurnComponent>(_otherPlayer)->getIsShooting() &&
            _entityManager->getComponentFromEntity<TurnComponent>(_currentPlayer)->getIsShooting()) {

            Weapon *selectedWeapon = _entityManager->getComponentFromEntity<PlayerComponent>(
                    _currentPlayer)->getSelectedWeapon();

            if (_entityManager->getComponentFromEntity<TurnComponent>(_currentPlayer)->getEnergy() >= _entityManager->getComponentFromEntity<PlayerComponent>(_currentPlayer)->getSelectedWeapon()->getEnergyCost() &&
                selectedWeapon->getAmmo() > 0) {

                auto currentPlayerPos = _entityManager->getComponentFromEntity<PositionComponent>(_currentPlayer);
                auto playerSize = _entityManager->getComponentFromEntity<BoxCollider>(_currentPlayer);
                int playerCenterX = currentPlayerPos->X + playerSize->width / 2.0;
                int playerCenterY = currentPlayerPos->Y + playerSize->height / 2.0;

                double deltaX = event.getXPosition() - playerCenterX;
                double deltaY = event.getYPosition() - playerCenterY;

                // shooting in a circle
                double totalLength = sqrt(deltaX * deltaX + deltaY * deltaY);
                double length =
                        totalLength > _projectileBuilder.maxVeloctiy ? _projectileBuilder.maxVeloctiy : totalLength;
                double scale = length / totalLength;

                deltaX *= scale;
                deltaY *= scale;

                double toX = playerCenterX + deltaX;
                double toY = playerCenterY + deltaY;

                if (!_powerBar.isVisible()) {
                    _powerBar.show();
                    _powerBar.lockToPlayer(_currentPlayer);
                }

                if (event.getMouseEventType() == MouseEventType::Down &&
                    event.getMouseClickType() == MouseClickType::Left) {
                    _shootingLine.setFromX(playerCenterX);
                    _shootingLine.setFromY(playerCenterY);
                    _shootingLine.setToX(toX);
                    _shootingLine.setToY(toY);
                    _shootingLine.show();
                    _mouseDown = true;
                }

                if (event.getMouseEventType() == MouseEventType::Drag) {
                    _shootingLine.setFromX(playerCenterX);
                    _shootingLine.setFromY(playerCenterY);
                    _shootingLine.setToX(toX);
                    _shootingLine.setToY(toY);
                    _shootingLine.show();
                }

                if (event.getMouseEventType() == MouseEventType::Up &&
                    event.getMouseClickType() == MouseClickType::Left && _mouseDown) {
                    generateProjectile(*currentPlayerPos, *playerSize, deltaX, deltaY, selectedWeapon, playerCenterX, playerCenterY);
                    _projectileFired = true;
                    _entityManager->getComponentFromEntity<TurnComponent>(_currentPlayer)->lowerEnergy(_entityManager->getComponentFromEntity<PlayerComponent>(_currentPlayer)->getSelectedWeapon()->getEnergyCost());
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


void ShootingSystem::toggleShooting() {
    if (!_projectileFired) {
        setPlayerTurn();
        auto playerTurn = _entityManager->getComponentFromEntity<TurnComponent>(_currentPlayer);
        if (playerTurn != nullptr &&
            _entityManager->getComponentFromEntity<PlayerComponent>(_currentPlayer)->getSelectedWeaponAvailability() > 0 &&
            _entityManager->getComponentFromEntity<TurnComponent>(_currentPlayer)->getEnergy() >= _entityManager->getComponentFromEntity<PlayerComponent>(_currentPlayer)->getSelectedWeapon()->getEnergyCost()) {
            playerTurn->changeIsShooting();
            if (!playerTurn->getIsShooting())
                resetShooting();
            else {
                _entityManager->getComponentFromEntity<MoveComponent>(_currentPlayer)->xVelocity = 0;
            }
        }
    }
}

void ShootingSystem::resetShooting() {
    _mouseDown = false;
    _shootingLine.hide();
    _powerBar.hide();
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
    _projectile = _projectileBuilder
            .setPlayerPostion(playerPositionComponent)
            .setPlayerCollider(playerCollider)
            .setXVelocity(velocityX)
            .setYVelocity(velocityY)
            .setPower(_powerBar.getPower())
            .setWeapon(*selectedWeapon)
            .setPlayerCenterX(playerCenterX)
            .setPlayerCenterY(playerCenterY)
            .build();
    selectedWeapon->lowerAmmo();
}
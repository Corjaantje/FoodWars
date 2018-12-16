#include "../../../../Headers/GameECS/Systems/Misc/PowerBar.h"
#include "../../../../Headers/GameECS/Components/DrawableComponent.h"
#include "../../../../../TonicEngine/Headers/Visual/Shapes/ShapeRectangle.h"
#include "../../../../Headers/GameECS/Components/AnimationComponent.h"
#include "../../../../Headers/GameECS/Components/PositionComponent.h"
#include "../../../../Headers/GameECS/Components/Collider/BoxCollider.h"

PowerBar::PowerBar(EntityManager &entityManager) : _entityManager{&entityManager}, _powerBarBackground{-1},
                                                   _risingPower{true},
                                                   _powerBar{-1}, _timePassed{0}, _playerId{-1}, _power{0},
                                                   _powerBarRect{nullptr}, _playerCollider{nullptr},
                                                   _playerPosition{nullptr} {

}

void PowerBar::update(double dt) {
    if (_playerId > 0 && _powerBar > 0) {
        _timePassed += dt;

        if (_timePassed >= 0.02) {
            _timePassed = 0;
            if (!_risingPower) {
                if (_power > 0) {
                    _power--;
                } else {
                    _risingPower = true;
                }
            } else {
                if (_power < 50) {
                    _power++;
                } else {
                    _risingPower = false;
                }
            }

            int playerCenterX = static_cast<int>(_playerPosition->X + _playerCollider->width / 2.0);
            int playerCenterY = static_cast<int>(_playerPosition->Y + _playerCollider->height / 2.0);

            int height = _power * -1;

            if (!_powerBarRect) {
                int powerBarX;
                // Check if player is looking left or right to determine the x position of the powerbar
                if (!_entityManager->getComponentFromEntity<AnimationComponent>(_playerId)->getIsLookingLeft())
                    powerBarX = playerCenterX - 55;
                else
                    powerBarX = playerCenterX + 35;
                int powerBarY = playerCenterY - 25;

                int width = 16;
                int xPos = powerBarX + 2;
                int yPos = powerBarY + 50;
                _entityManager->addComponentToEntity<DrawableComponent>(_powerBarBackground,
                                                                        std::make_unique<ShapeRectangle>(20, 50,
                                                                                                         powerBarX,
                                                                                                         powerBarY,
                                                                                                         Colour(0, 0, 0,
                                                                                                                0)));
                _powerBarRect = static_cast<ShapeRectangle *>(_entityManager->addComponentToEntity<DrawableComponent>(
                        _powerBar,
                        std::make_unique<ShapeRectangle>(width, height, xPos, yPos, Colour(255, 0, 0, 0),
                                                         2)).getShape());
            }
            _powerBarRect->height = height;
        }
    }
}

void PowerBar::show() {
    if (_powerBar < 0 || _powerBarBackground < 0) {
        _powerBar = _entityManager->createEntity();
        _powerBarBackground = _entityManager->createEntity();
    }
}

void PowerBar::hide() {
    _entityManager->removeEntity(_powerBarBackground);
    _entityManager->removeEntity(_powerBar);
    _powerBarBackground = -1;
    _powerBar = -1;
    _powerBarRect = nullptr;
    _risingPower = true;
    _power = 0;
    _timePassed = 0;
}

void PowerBar::lockToPlayer(int playerId) {
    _playerId = playerId;
    _playerPosition = _entityManager->getComponentFromEntity<PositionComponent>(_playerId);
    _playerCollider = _entityManager->getComponentFromEntity<BoxCollider>(_playerId);
}

int PowerBar::getPower() const {
    return _power;
}

bool PowerBar::isVisible() const {
    return _playerId > 0 && _powerBarBackground > 0 && _powerBar > 0;
}

PowerBar::~PowerBar() {
    if (isVisible())
        hide();
}

void PowerBar::setPower(int power) {
    _power = power;
    _timePassed = 1;
}

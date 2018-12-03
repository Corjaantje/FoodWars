#ifndef PROJECT_SWA_SHOOTSYSTEM_H
#define PROJECT_SWA_SHOOTSYSTEM_H

#include "IBaseSystem.h"
#include "../../../../TonicEngine/Headers/Events/MouseEvent.h"
#include "../../../../TonicEngine/Headers/Input/IObserver.h"
#include "../../../Headers/GameECS/Components/MoveComponent.h"
#include "../../../Headers/GameECS/Components/AnimationComponent.h"
#include "../../../../TonicEngine/Headers/Visual/VisualFacade.h"
#include "../../../../TonicEngine/Headers/Input/InputFacade.h"
#include "../../../../TonicEngine/Headers/Audio/AudioFacade.h"
#include "../Components/Collider/BoxCollider.h"
#include "../../StateMachine/Misc/Weapon.h"

class ShootingSystem : public IBaseSystem, public IObserver<MouseEvent> {
public:
    ShootingSystem(EntityManager &entityManager, std::shared_ptr<AudioFacade> audioFacade,
                            std::shared_ptr<VisualFacade> visualFacade, std::shared_ptr<InputFacade> inputFacade);
    ~ShootingSystem() override;

    void update(double deltaTime) override;
    void update(std::shared_ptr<MouseEvent> event) override;
    void toggleShooting();

    void createShootingLine(int fromX, int fromY, int toX, int toY);
    void createPowerBar();
    void powerHandler();
private:
    bool _isShooting;
    bool _projectileFired;
    bool _lineDrawn;
    bool _mouseDown;
    int _projectile;
    int _powerBarX;
    int _powerBarY;
    double _power;
    int _powerBarWidth;
    int _maxPower;
    double _timePassed;
    int _shootingLine;
    int _powerBarBackground;
    int _powerBar;

    std::shared_ptr<AudioFacade> _audioFacade;
    EntityManager *_entityManager;
    std::shared_ptr<VisualFacade> _visualFacade;
    Renderlist _renderList;

    void resetShooting();

    void generateProjectile(const PositionComponent &playerPositionComponent, const BoxCollider &playerCollider,
                            double velocityX, double velocityY, Weapon* selectedWeapon);
};

#endif //PROJECT_SWA_SHOOTSYSTEM_H

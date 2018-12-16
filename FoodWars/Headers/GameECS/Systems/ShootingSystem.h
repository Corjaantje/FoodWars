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
#include "Misc/ProjectileBuilder.h"
#include "Misc/LineDrawer.h"
#include "Misc/PowerBar.h"

class ShootingSystem : public IBaseSystem, public IObserver<MouseEvent> {
public:
    ShootingSystem(EntityManager &entityManager, AudioFacade& audioFacade, VisualFacade& visualFacade, InputFacade& inputFacade);

    void update(double deltaTime) override;
    void update(const MouseEvent& event) override;
    void toggleShooting();
private:
    LineDrawer _shootingLine;
    PowerBar _powerBar;
    bool _projectileFired;
    bool _mouseDown;
    int _projectile;

    int _currentPlayer;
    int _otherPlayer;

    AudioFacade* _audioFacade;
    VisualFacade* _visualFacade;
    EntityManager *_entityManager;
    Renderlist _renderList;

    ProjectileBuilder _projectileBuilder;
    void resetShooting();
    void setPlayerTurn();
    void generateProjectile(const PositionComponent &playerPositionComponent, const BoxCollider &playerCollider,
                            double velocityX, double velocityY, Weapon* selectedWeapon, int playerCenterX, int playerCenterY);
};

#endif //PROJECT_SWA_SHOOTSYSTEM_H

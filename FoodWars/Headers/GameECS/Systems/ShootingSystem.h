#ifndef PROJECT_SWA_SHOOTSYSTEM_H
#define PROJECT_SWA_SHOOTSYSTEM_H

#include "IBaseSystem.h"
#include "../../../../TonicEngine/Headers/Events/MouseEvent.h"
#include "../../../../TonicEngine/Headers/Input/IObserver.h"
#include "../../../Headers/GameECS/Components/MoveComponent.h"
#include "../../../../TonicEngine/Headers/Visual/VisualFacade.h"
#include "../../../../TonicEngine/Headers/Input/InputFacade.h"
#include "../../../../TonicEngine/Headers/Audio/AudioFacade.h"
#include "../Components/Collider/BoxCollider.h"

class ShootingSystem : public IBaseSystem, public IObserver<MouseEvent> {
public:
    ShootingSystem(EntityManager &entityManager, AudioFacade& audioFacade, VisualFacade& visualFacade, InputFacade& inputFacade);

    void update(double deltaTime) override;
    void update(const MouseEvent& event) override;
    void toggleShooting();

    void createShootingLine(int fromX, int fromY, int toX, int toY);
private:
    bool _isShooting;
    bool _projectileFired;
    int _projectile;
    int _shootingLine;
    AudioFacade* _audioFacade;
    VisualFacade* _visualFacade;
    EntityManager *_entityManager;
    Renderlist _renderList;

    void generateProjectile(const PositionComponent &playerPositionComponent, const BoxCollider &playerCollider,
                            double velocityX, double velocityY);
};

#endif //PROJECT_SWA_SHOOTSYSTEM_H

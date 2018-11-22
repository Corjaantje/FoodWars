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

class ShootingSystem : public IBaseSystem, public IObserver<MouseEvent>
{
public:
    explicit ShootingSystem(std::shared_ptr<EntityManager> entityManager, std::shared_ptr<AudioFacade> audioFacade, std::shared_ptr<VisualFacade> visualFacade, std::shared_ptr<InputFacade> inputFacade);
    ~ShootingSystem() override;

    void update(double deltaTime) override;
    void update(std::shared_ptr<MouseEvent> event) override;
    void toggleShooting();

    void createShootingLine(int fromX, int fromY, int toX, int toY);
private:
    bool _isShooting;
    bool _projectileFired;
    int _projectile;
    int _shootingLine;
    std::shared_ptr<AudioFacade> _audioFacade;
    std::shared_ptr<EntityManager> _entityManager;
    std::shared_ptr<VisualFacade> _visualFacade;
    Renderlist _renderList;

    void generateProjectile(const PositionComponent &playerPositionComponent, const BoxCollider &playerCollider,
                            double velocityX, double velocityY);
};

#endif //PROJECT_SWA_SHOOTSYSTEM_H

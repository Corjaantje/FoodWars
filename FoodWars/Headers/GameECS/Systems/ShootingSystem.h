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

class ShootingSystem : public IBaseSystem, public IObserver<MouseEvent> {
public:
    ShootingSystem(EntityManager &entityManager, std::shared_ptr<AudioFacade> audioFacade,
                            std::shared_ptr<VisualFacade> visualFacade, std::shared_ptr<InputFacade> inputFacade);
    ~ShootingSystem() override;

    void update(double deltaTime) override;
    void update(std::shared_ptr<MouseEvent> event) override;
    void toggleShooting();

    void createShootingLine(int fromX, int fromY, int toX, int toY);
    void createPowerBar(int width, int height, int xPos, int yPos);
    void powerHandler(int width, int height, int xPos, int yPos);
private:
    bool _isShooting;
    bool _projectileFired;
    bool _lineDrawn;
    int _projectile;
    int _shootingLine;
    int _powerBarBackground;
    int _powerBar;
    double _timePassed;

    std::shared_ptr<AudioFacade> _audioFacade;
    EntityManager *_entityManager;
    std::shared_ptr<VisualFacade> _visualFacade;
    Renderlist _renderList;

    void generateProjectile(const PositionComponent &playerPositionComponent, const BoxCollider &playerCollider,
                            double velocityX, double velocityY);
};

#endif //PROJECT_SWA_SHOOTSYSTEM_H

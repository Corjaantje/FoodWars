#include <utility>
#include <iostream>
#include "../../../Headers/GameECS/Systems/DrawSystem.h"
#include "../../../Headers/GameECS/Components/DrawableComponent.h"
#include "../../../Headers/GameECS/Components/TurnComponent.h"
#include "../../../Headers/GameECS/Components/PositionComponent.h"
#include "../../../Headers/GameECS/Components/DamageableComponent.h"
#include "../../../Headers/GameECS/Components/PlayerComponent.h"

DrawSystem::DrawSystem(EntityManager &entityManager,
                       std::shared_ptr<VisualFacade> visualFacade,
                       std::shared_ptr<InputFacade> inputFacade) : _inputFacade{std::move(inputFacade)},
                                                                   _entityManager{&entityManager},
                                                                   _visualFacade{std::move(visualFacade)},
                                                                   _updateCallCount{0},
                                                                   _timeLast{
                                                                           std::chrono::steady_clock::now().time_since_epoch()} {
}

DrawSystem::~DrawSystem() = default;

void DrawSystem::update(double dt) {
    std::map<int, DrawableComponent *> drawComps = _entityManager->getAllEntitiesWithComponent<DrawableComponent>();
    _renderList._shapes.clear();
    _updateCallCount++;
    drawNonComponents();
    drawPlayers();
    //Draw Components
    for (const auto &iterator: _entityManager->getAllEntitiesWithComponent<DrawableComponent>()) {
        auto *positionComponent = _entityManager->getComponentFromEntity<PositionComponent>(iterator.first);
        if (positionComponent) {
            iterator.second->getShape()->xPos = positionComponent->X;
            iterator.second->getShape()->yPos = positionComponent->Y;
        }
        iterator.second->getShape()->addToRender(&_renderList);
    }
    _visualFacade->render(_renderList);
}

void DrawSystem::drawNonComponents() {
    _renderList._shapes[2].push_back(createShape<ShapeSprite>(1600, 900, 0, 0, "ScreenGameSmallUI.png"));

    if(!_playerIconOne.empty()) {
        _renderList._shapes[3].push_back(createShape<ShapeSprite>(36, 54, 47, 40, _playerIconOne));
    }
    if(!_playerIconTwo.empty()) {
        _renderList._shapes[3].push_back(createShape<ShapeSprite>(36, 54, 1515, 40, _playerIconTwo));
    }
    //Framerate
    std::chrono::duration<double> currentTime = std::chrono::steady_clock::now().time_since_epoch();
    double loggen = currentTime.count() - _timeLast.count();
    if (loggen >= 1) {
        _fpsString = "FPS: " + std::to_string(_updateCallCount);
        _timeLast = std::chrono::steady_clock::now().time_since_epoch();
        _updateCallCount = 0;
    }
    if (_showFPS) {
        _renderList._shapes[3].push_back(
                createShape<ShapeText>(27, 155, _fpsString, 180, 75, 37, Colour(255, 255, 255, 0)));
    }
    drawPlayerStats();
}

void DrawSystem::drawPlayers() {
    _playerUpdateCount++;
    if (_playerUpdateCount > 30) {
        std::map<int, PlayerComponent *> playerComps = _entityManager->getAllEntitiesWithComponent<PlayerComponent>();
        for (auto const& x : playerComps)
        {
            if(x.second->getPlayerID() == 1){
                auto *sprite = dynamic_cast<ShapeSprite *>(_entityManager->getComponentFromEntity<DrawableComponent>(
                        x.first)->getShape());
               if(sprite != nullptr) {
                   _playerIconOne = sprite->imageURL;
               }
            }
            if(x.second->getPlayerID() == 2){
                auto *sprite = dynamic_cast<ShapeSprite *>(_entityManager->getComponentFromEntity<DrawableComponent>(
                        x.first)->getShape());
                if(sprite != nullptr) {
                    _playerIconTwo = sprite->imageURL;
                }
            }
        }
        _playerUpdateCount = 0;
    }
}

bool DrawSystem::toggleFpsCounter() {
    _showFPS = !_showFPS;
}

void DrawSystem::drawPlayerStats() {
//Draw Turn Timer and HP
    for(const auto &iterator: _entityManager->getAllEntitiesWithComponent<PlayerComponent>()) {
        if(iterator.second->getPlayerID() == 1) {
            int hpWidth = _entityManager->getComponentFromEntity<DamageableComponent>(iterator.first)->GetHealth();
            _renderList._shapes[3].push_back(createShape<ShapeText>(150, 27, std::to_string(hpWidth),180, 40, 25, Colour(255, 255, 255, 0)));
            _renderList._shapes[2].push_back(createShape<ShapeRectangle>(hpWidth*1.5, 25, 150, 27, getConvertedHealthColor(hpWidth)));

            auto turnComp = _entityManager->getComponentFromEntity<TurnComponent>(iterator.first);
            int energy = static_cast<int>(turnComp->getEnergy());
            if(energy < 0){
                energy = 0;
            }
            _renderList._shapes[3].push_back(createShape<ShapeText>(150, 70, std::to_string(energy),180, 40, 25, Colour(255, 255, 255, 0)));
            _renderList._shapes[2].push_back(createShape<ShapeRectangle>(energy*1.5, 25, 150, 69, Colour(0, 191, 255, 0)));
            if(turnComp->isMyTurn()){
                double time = turnComp->getRemainingTime();
                std::string text;
                if (time < 10) {
                    text = std::to_string(time).substr(0, 3);
                } else {
                    text = std::to_string(time).substr(0, 4);
                }
                _renderList._shapes[3].push_back(
                        createShape<ShapeText>(800, 45, text, 180, 75, 37, Colour(255, 255, 255, 0)));
            }
            if(!iterator.second->getSelectedWeapon().empty()){
                _renderList._shapes[3].push_back(createShape<ShapeSprite>(15, 30, 396, 45, iterator.second->getSelectedWeapon()));
            }
            _renderList._shapes[3].push_back(createShape<ShapeText>(391, 82, std::to_string(iterator.second->getSelectedWeaponAvailability()),180, 30, 30, Colour(255, 255, 255, 0)));

        }
        if(iterator.second->getPlayerID() == 2){
            int hpWidth = _entityManager->getComponentFromEntity<DamageableComponent>(iterator.first)->GetHealth();
            _renderList._shapes[3].push_back(createShape<ShapeText>(1300 + 80, 27, std::to_string(hpWidth),180, 40, 25, Colour(255, 255, 255, 0)));
            _renderList._shapes[2].push_back(createShape<ShapeRectangle>(hpWidth*1.3, 25, 1300-hpWidth*1.3 + 130, 27, getConvertedHealthColor(hpWidth)));

            auto turnComp = _entityManager->getComponentFromEntity<TurnComponent>(iterator.first);
            int energy = static_cast<int>(turnComp->getEnergy());
            if(energy < 0){
                energy = 0;
            }
            _renderList._shapes[3].push_back(createShape<ShapeText>(1300 + 80, 70, std::to_string(energy),180, 40, 25, Colour(255, 255, 255, 0)));
            _renderList._shapes[2].push_back(createShape<ShapeRectangle>(energy*1.3, 25, 1300-energy*1.3 + 130, 69, Colour(0, 191, 255, 0)));

            if(turnComp->isMyTurn()){
                double time = turnComp->getRemainingTime();
                std::string text;
                if (time < 10) {
                    text = std::to_string(time).substr(0, 3);
                } else {
                    text = std::to_string(time).substr(0, 4);
                }
                _renderList._shapes[3].push_back(
                        createShape<ShapeText>(800, 45, text, 180, 75, 37, Colour(255, 255, 255, 0)));
            }
            if(!iterator.second->getSelectedWeapon().empty()){
                _renderList._shapes[3].push_back(createShape<ShapeSprite>(15, 30, 1190, 45, iterator.second->getSelectedWeapon()));
            }
            _renderList._shapes[3].push_back(createShape<ShapeText>(1185, 82, std::to_string(iterator.second->getSelectedWeaponAvailability()), 180, 30, 30, Colour(255, 255, 255, 0)));
        }
    }
}

Colour DrawSystem::getConvertedHealthColor(int health) {
    return Colour(255-(health*2), 0+(health*2), 55, 0);
}
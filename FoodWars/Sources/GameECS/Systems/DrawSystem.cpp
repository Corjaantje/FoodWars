#include <utility>
#include <iostream>
#include "../../../Headers/GameECS/Systems/DrawSystem.h"
#include "../../../Headers/GameECS/Components/DrawableComponent.h"
#include "../../../Headers/GameECS/Components/TurnComponent.h"
#include "../../../Headers/GameECS/Components/PositionComponent.h"
#include "../../../Headers/GameECS/Components/DamageableComponent.h"
#include "../../../Headers/GameECS/Components/PlayerComponent.h"
#include "../../../Headers/GameECS/Components/AIComponent.h"
#include "../../../../TonicEngine/Headers/Visual/Shapes/TextButton.h"

DrawSystem::DrawSystem(EntityManager &entityManager, VisualFacade& visualFacade, InputFacade& inputFacade) :
       _entityManager{&entityManager},
       _visualFacade{&visualFacade},
       _inputFacade(&inputFacade),
       _updateCallCount{0},
       _timeLast {std::chrono::steady_clock::now().time_since_epoch()},
       _weaponSelection(entityManager)
{
    // weapon selection for player 1
    drawWeaponSelection(340, 1, "previous");
    drawWeaponSelection(442, 1, "next");
    // weapon selection for player 2
    drawWeaponSelection(1134, 2, "previous");
    drawWeaponSelection(1236, 2, "next");
}

DrawSystem::~DrawSystem() = default;

void DrawSystem::update(double dt) {
    std::map<int, DrawableComponent *> drawComps = _entityManager->getAllEntitiesWithComponent<DrawableComponent>();
    _renderList._shapes.clear();
    _updateCallCount++;
    drawNonComponents();
    drawPlayers();
    for (const auto& shape : _shapes )
        shape->addToRender(&_renderList);

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
        std::map<int, TurnComponent *> playerComps = _entityManager->getAllEntitiesWithComponent<TurnComponent>();
        for (auto const& x : playerComps)
        {
            auto player = _entityManager->getComponentFromEntity<PlayerComponent>(x.first); // Check for players
            if(player != nullptr){
                if (player->getPlayerID() == 1) {
                    auto *sprite = dynamic_cast<ShapeSprite *>(_entityManager->getComponentFromEntity<DrawableComponent>(
                            x.first)->getShape());
                    if (sprite != nullptr) {
                        _playerIconOne = sprite->imageURL;
                    }
                }
                if (player->getPlayerID() == 2) {
                    auto *sprite = dynamic_cast<ShapeSprite *>(_entityManager->getComponentFromEntity<DrawableComponent>(
                            x.first)->getShape());
                    if (sprite != nullptr) {
                        _playerIconTwo = sprite->imageURL;
                    }
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
    for(const auto &iterator: _entityManager->getAllEntitiesWithComponent<TurnComponent>()) {

        auto player = _entityManager->getComponentFromEntity<PlayerComponent>(iterator.first); // Check for players
        if(player != nullptr){
            if (player->getPlayerID() == 1) {
                int hpWidth = _entityManager->getComponentFromEntity<DamageableComponent>(iterator.first)->getHealth();
                // for(const auto &iterator: _entityManager->getAllEntitiesWithComponent<PlayerComponent>()) {
                //     if(iterator.second->getPlayerID() == 1) {
                //        int hpWidth = _entityManager->getComponentFromEntity<DamageableComponent>(iterator.first)->getHealth();
                _renderList._shapes[3].push_back(createShape<ShapeText>(150, 27, std::to_string(hpWidth), 180, 40, 25,
                                                                        Colour(255, 255, 255, 0)));
                _renderList._shapes[2].push_back(
                        createShape<ShapeRectangle>(hpWidth * 1.5, 25, 150, 27, getConvertedHealthColor(hpWidth)));

                //auto turnComp = _entityManager->getComponentFromEntity<TurnComponent>(iterator.first);
                int energy = static_cast<int>(iterator.second->getEnergy());
                if (energy < 0) {
                    energy = 0;
                }
                _renderList._shapes[3].push_back(
                        createShape<ShapeText>(150, 70, std::to_string(energy), 180, 40, 25, Colour(255, 255, 255, 0)));
                _renderList._shapes[2].push_back(
                        createShape<ShapeRectangle>(energy * 1.5, 25, 150, 69, Colour(0, 191, 255, 0)));
                if (iterator.second->isMyTurn()) {
                    double time = iterator.second->getRemainingTime();
                    std::string text = std::to_string(time).substr(0, 4);
                    Colour timeColour = Colour(255, 255, 255, 0);
                    if (time < 10) {
                        text = std::to_string(time).substr(0, 3);
                        timeColour = Colour(255, 165, 0, 0);
                    }
                    if (time < 5) {
                        text = std::to_string(time).substr(0, 3);
                        timeColour = Colour(255, 0, 0, 0);
                    }
                    _renderList._shapes[3].push_back(createShape<ShapeText>(800, 45, text, 180, 75, 37, timeColour));
                }
                if (player->getSelectedWeapon() != nullptr) {
                    _renderList._shapes[3].push_back(createShape<ShapeSprite>(15, 30, 396, 45,
                                                                              player->getSelectedWeapon()->getImage()));
                }
                _renderList._shapes[3].push_back(
                        createShape<ShapeText>(391, 82, std::to_string(player->getSelectedWeaponAvailability()), 180,
                                               30, 30, Colour(255, 255, 255, 0)));

            }
            if (player->getPlayerID() == 2) {
                int hpWidth = _entityManager->getComponentFromEntity<DamageableComponent>(iterator.first)->getHealth();
                _renderList._shapes[3].push_back(
                        createShape<ShapeText>(1300 + 80, 27, std::to_string(hpWidth), 180, 40, 25,
                                               Colour(255, 255, 255, 0)));
                _renderList._shapes[2].push_back(
                        createShape<ShapeRectangle>(hpWidth * 1.3, 25, 1300 - hpWidth * 1.3 + 130, 27,
                                                    getConvertedHealthColor(hpWidth)));

                auto turnComp = _entityManager->getComponentFromEntity<TurnComponent>(iterator.first);
                int energy = static_cast<int>(turnComp->getEnergy());
                if (energy < 0) {
                    energy = 0;
                }
                _renderList._shapes[3].push_back(
                        createShape<ShapeText>(1300 + 80, 70, std::to_string(energy), 180, 40, 25,
                                               Colour(255, 255, 255, 0)));
                _renderList._shapes[2].push_back(
                        createShape<ShapeRectangle>(energy * 1.3, 25, 1300 - energy * 1.3 + 130, 69,
                                                    Colour(0, 191, 255, 0)));

                if (turnComp->isMyTurn()) {
                    double time = turnComp->getRemainingTime();
                    std::string text = std::to_string(time).substr(0, 4);
                    Colour timeColour = Colour(255, 255, 255, 0);
                    if (time < 10) {
                        text = std::to_string(time).substr(0, 3);
                        timeColour = Colour(255, 165, 0, 0);
                    }
                    if (time < 5) {
                        text = std::to_string(time).substr(0, 3);
                        timeColour = Colour(255, 0, 0, 0);
                    }
                    _renderList._shapes[3].push_back(createShape<ShapeText>(800, 45, text, 180, 75, 37, timeColour));
                }
                if (player->getSelectedWeapon() != nullptr) {
                    _renderList._shapes[3].push_back(createShape<ShapeSprite>(15, 30, 1190, 45,
                                                                              player->getSelectedWeapon()->getImage()));
                }
                _renderList._shapes[3].push_back(
                        createShape<ShapeText>(1185, 82, std::to_string(player->getSelectedWeaponAvailability()), 180,
                                               30, 30, Colour(255, 255, 255, 0)));
            }
        }
    }
}

Colour DrawSystem::getConvertedHealthColor(int health) {
    return Colour(255-(health*2), 0+(health*2), 55, 0);
}

void DrawSystem::drawWeaponSelection(int x, int playerId, std::string selection) {
    _renderList._shapes[3].push_back(
            createShape<SpriteButton>(_inputFacade->getMouseEventObservable(),"carrot.png",
                                      [this, playerId, selection]() {
                                            _weaponSelection.newSelectedWeapon(playerId, selection);
                                      },
                                      27, 27, x, 45,
                                      Colour{0,0,0,0}));
}

void DrawSystem::addShape(IShape *shape) {
    _shapes.push_back(shape);
}

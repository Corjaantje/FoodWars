#include "../../../Headers/StateMachine/Misc/WeaponSelection.h"
#include "../../../Headers/GameECS/Components/TurnComponent.h"

WeaponSelection::WeaponSelection(EntityManager &entityManager) : _entityManager(&entityManager) {

}

void WeaponSelection::newSelectedWeapon(int playerId, std::string selection) {
    std::map<int, PlayerComponent *> playerComps = _entityManager->getAllEntitiesWithComponent<PlayerComponent>();
    for (auto const &playerComp : playerComps) {
        if (playerComp.second->getPlayerID() == playerId) {
            if (selection == "previous") {
                playerComp.second->setSelectedWeapon("previous");
            } else if (selection == "next") {
                playerComp.second->setSelectedWeapon("next");
            }
        }
    }
}

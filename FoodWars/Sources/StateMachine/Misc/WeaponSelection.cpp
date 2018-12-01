#include "../../../Headers/StateMachine/Misc/WeaponSelection.h"

WeaponSelection::WeaponSelection() : _entityManager(new EntityManager) {
    /*std::map<int, PlayerComponent *> playerComps = _entityManager.getAllEntitiesWithComponent<PlayerComponent>();
    renderlist.clearLists();
    for (const auto &drawComp : drawComps) {
        drawComp.second->getShape()->addToRender(&renderlist);
    }*/
}

WeaponSelection::~WeaponSelection() {

}

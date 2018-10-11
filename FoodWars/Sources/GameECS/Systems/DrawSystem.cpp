#include "../../../Headers/GameECS/Systems/DrawSystem.h"
#include "../../../Headers/GameECS/Systems/IBaseSystem.h"

DrawSystem::DrawSystem(EntityManager *entityManager){
    _entityManager = entityManager;
}

DrawSystem::~DrawSystem() {

}
void DrawSystem::update(double dt) {
}
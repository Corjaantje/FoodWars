#include "TonicEngine/Headers/Visual/Window.h"
#include "TonicEngine/Headers/Visual/VisualFacade.h"
#include "TonicEngine/Headers/Input/InputObservable.h"
#include "TonicEngine/Headers/Audio/AudioFacade.h"
#include "FoodWars/Headers/GameECS/Entities/EntityManager.h"
#include "FoodWars/Headers/GameECS/Systems/DrawSystem.h"
#include "FoodWars/Headers/GameECS/Components/DrawableComponent.h"


int main(int argc, char** argv)
{
    VisualFacade* visualFacade = new VisualFacade();
    InputObservable* inputObservable = new InputObservable();
    visualFacade->setTitle("Food Wars");
    //visualFacade->setResolution(1366, 768);
    visualFacade->setResolution(640, 480);
    visualFacade->disablefullscreen();
    ShapeRectangle rectangle(200, 200, 0, 0, Colour(0, 255, 0, 255));
    ShapeRectangle rectangle2(100, 100, 150, 150, Colour(0, 0, 255, 255));
    ShapeRectangle rectangle3(50, 50, 225, 225, Colour(255, 0, 0, 255));

    visualFacade->addRectangle(rectangle);
    visualFacade->addRectangle(rectangle2);
    visualFacade->addRectangle(rectangle3);

//    ShapeSprite sprite(150, 150, 200, 0, "../grass.bmp");
//    visualFacade->addSprite(sprite);
    visualFacade->openWindow();

    EntityManager _entityManager;
    int entity = _entityManager.createEntity(nullptr, 0);
    std::cout << "Number of entities with drawable component: " << _entityManager.getAllEntitiesWithComponent<DrawableComponent>().size() << std::endl;
    DrawableComponent d;
    d.xPos = 10;
    d.yPos = 11;
    _entityManager.addComponentToEntity(entity, &d);
    std::cout << "Number of entities with drawable component: " << _entityManager.getAllEntitiesWithComponent<DrawableComponent>().size() << std::endl;

//    std::shared_ptr<DrawableComponent> dc = _entityManager.getComponentFromEntity<DrawableComponent>(entity);
//    dc->draw();
//    dc->xPos = 120;

    //onderstaande code met test variabele werkt niet;
    DrawableComponent test = *_entityManager.getComponentFromEntity<DrawableComponent>(entity);
    test.xPos = 200;

    for(auto const& iterator: _entityManager.getAllEntitiesWithComponent<DrawableComponent>()){
        iterator.second->draw();
    }

    _entityManager.removeComponentFromEntity<DrawableComponent>(entity);
    std::cout << "Number of entities with drawable component: " << _entityManager.getAllEntitiesWithComponent<DrawableComponent>().size() << std::endl;

    _entityManager.addComponentToEntity(entity, new DrawableComponent(50,50));
    int entity2 = _entityManager.createEntity();
    _entityManager.addComponentToEntity(entity2, new DrawableComponent(99, 99));
    for(auto const& iterator: _entityManager.getAllEntitiesWithComponent<DrawableComponent>()){
        std::cout << iterator.first << ": ";
        iterator.second->draw();
    }

    _entityManager.removeEntity(entity);
    _entityManager.removeEntity(entity2);
    _entityManager.removeEntity(entity2);
    std::cout << "Number of entities with drawable component: " << _entityManager.getAllEntitiesWithComponent<DrawableComponent>().size() << std::endl;

    while(!visualFacade->isWindowClosed()){
        visualFacade->render();
        visualFacade->pollEvents();
        //inputObservable->pollEvents();
    }

    return 0;
}

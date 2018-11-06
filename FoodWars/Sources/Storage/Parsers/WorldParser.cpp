#include "../../../Headers/Storage/Parsers/WorldParser.h"

WorldParser::WorldParser(std::shared_ptr<EntityManager> ent) {
    _entityManager = ent;
}

WorldParser::~WorldParser() {

}

int* WorldParser::ParseFromXML(tinyxml2::XMLElement elem) {
    //TODO: Make actual loading function
    return 0;
}

void WorldParser::ParseToXML() {
    std::map<int, std::shared_ptr<DrawableComponent>> toSave {_entityManager->getAllEntitiesWithComponent<DrawableComponent>()};


    for (auto const& drawComp : toSave)
    {

    }
}
//void DrawSystem::generateTerrainDrawables(int x, int y) {
//    int randomNum = rand() % 19 + (-9);
//    int randomNum2 = rand() % 19 + (-9);
//    int randomNum3 = rand() % 19 + (-9);
//    int id = _entityManager->createEntity();
//    DrawableComponent *comp = new DrawableComponent();
//    _entityManager->addComponentToEntity(id, comp);
//    _entityManager->addComponentToEntity(id, new BoxCollider{16,16});
//    comp->shape = std::make_unique<ShapeRectangle>(ShapeRectangle({16, 16, x, y, Colour{149 + randomNum, 69 + randomNum2, 53 + randomNum3, 100}}));
//}
void WorldParser::ParseDrawableComponents(MyDocument& my_doc, std::map<int, std::shared_ptr<DrawableComponent>> toSave) {
    MyNode root { my_doc.GetRoot() };
    MyNode group_node { "drawables", &root };
    for (auto const& drawComp : toSave)
    {
        MyNode draw_node{ "drawcomponent", &group_node};

        // Does the "id" even matter? Dynamically assigning (on load) should work just as well
        MyNode id_node { "id", &draw_node};
        id_node.SetValue(0);


        MyNode shape_node { "shape", &draw_node};

        MyNode widthNode { "width", &shape_node };
        widthNode.SetValue(std::to_string(drawComp.second->shape->getWidth()));
        MyNode heightNode { "height", &shape_node };
        heightNode.SetValue(std::to_string(drawComp.second->shape->getHeight()));
        // MyNode colorNode { "color", &shape_node };
        // colorNode.SetValue(IDK MAN)

        shape_node.AddChild(widthNode);
        shape_node.AddChild(heightNode);

        //draw_node.AddChild(id_node);
        draw_node.AddChild(shape_node);

        group_node.AddChild(draw_node);
    }
    root.AddChild(group_node);

}





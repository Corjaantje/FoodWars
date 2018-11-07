#include "../../../Headers/Storage/Parsers/WorldParser.h"
WorldParser::WorldParser() {

}


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
MyDocument WorldParser::ParseDrawableComponents(MyDocument& my_doc, std::map<int, std::shared_ptr<DrawableComponent>> toSave) {
    MyNode root { my_doc.GetRoot() };
    MyNode group_node { "drawables", &root };
    for (auto const& drawComp : toSave)
    {
        MyNode drawNode{ "drawcomponent", &group_node};

        // Does the "id" even matter? Dynamically assigning (on load) should work just as well
        MyNode idNode { "id", &drawNode};
        idNode.SetValue(std::to_string(0));

        // Gathering values of the "shape"
        MyNode shapeNode { "shape", &drawNode};

        MyNode widthNode { "width", &shapeNode };
        widthNode.SetValue(std::to_string(drawComp.second->shape->getWidth()));
        MyNode heightNode { "height", &shapeNode };
        heightNode.SetValue(std::to_string(drawComp.second->shape->getHeight()));
        // MyNode colorNode { "color", &shape_node };
        // colorNode.SetValue(IDK MAN)

        shapeNode.AddChild(widthNode);
        shapeNode.AddChild(heightNode);
        //shape_node.AddChild(colorNode);

        MyNode positionNode { "position", &drawNode};

        MyNode xPos { "xpos", &positionNode};
        xPos.SetValue(std::to_string(drawComp.second->shape->xPos));
        MyNode yPos { "ypos", &positionNode};
        yPos.SetValue(std::to_string(drawComp.second->shape->yPos));

        positionNode.AddChild(yPos);
        positionNode.AddChild(xPos);

        //draw_node.AddChild(id_node);
        drawNode.AddChild(shapeNode);
        drawNode.AddChild(positionNode);

        group_node.AddChild(drawNode);
    }
    root.AddChild(group_node);
    my_doc.AddToRoot(group_node);
    return my_doc;
}





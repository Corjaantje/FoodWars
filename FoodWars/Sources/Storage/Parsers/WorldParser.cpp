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

MyDocument WorldParser::ParseDrawableComponents(MyDocument& my_doc, std::map<int, std::shared_ptr<DrawableComponent>> toSave) {
    MyNode root { my_doc.GetRoot() };
    MyNode group_node { "drawables", &root };
    for (auto const& drawComp : toSave)
    {
        MyNode drawNode{ "drawcomponent", &group_node};

        MyNode idNode { "id", &drawNode};
        idNode.SetValue(std::to_string(0));

        MyNode shapeNode { "shape", &drawNode};

        MyNode widthNode { "width", &shapeNode };
        widthNode.SetValue(std::to_string(drawComp.second->shape->getWidth()));
        MyNode heightNode { "height", &shapeNode };
        heightNode.SetValue(std::to_string(drawComp.second->shape->getHeight()));

        shapeNode.AddChild(widthNode);
        shapeNode.AddChild(heightNode);

        MyNode positionNode { "position", &drawNode};

        MyNode xPos { "xpos", &positionNode};
        xPos.SetValue(std::to_string(drawComp.second->shape->xPos));
        MyNode yPos { "ypos", &positionNode};
        yPos.SetValue(std::to_string(drawComp.second->shape->yPos));

        positionNode.AddChild(yPos);
        positionNode.AddChild(xPos);

        drawNode.AddChild(shapeNode);
        drawNode.AddChild(positionNode);

        group_node.AddChild(drawNode);
    }
    root.AddChild(group_node);
    my_doc.AddToRoot(group_node);
    return my_doc;
}





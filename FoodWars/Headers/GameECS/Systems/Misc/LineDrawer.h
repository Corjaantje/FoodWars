#ifndef PROJECT_SWA_LINEDRAWER_H
#define PROJECT_SWA_LINEDRAWER_H

#include "../../Entities/EntityManager.h"
#include "../../../../../TonicEngine/Headers/Visual/Shapes/ShapeLine.h"

class LineDrawer {
private:
    EntityManager *_entityManager;
    int _lineId;
    ShapeLine *_displayedLine;
    ShapeLine _line;
public:
    explicit LineDrawer(EntityManager &entityManger);

    void show();

    void hide();

    void setFromX(int x);

    void setFromY(int y);

    void setToX(int x);

    void setToY(int y);
};

#endif //PROJECT_SWA_LINEDRAWER_H

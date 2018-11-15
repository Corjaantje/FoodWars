#ifndef PROJECT_SWA_ENTITYMOMENTO_H
#define PROJECT_SWA_ENTITYMOMENTO_H


class EntityMemento {
public:
    EntityMemento(int entityID);
    int getState() const;
private:
    int _entityId;
};


#endif //PROJECT_SWA_ENTITYMOMENTO_H

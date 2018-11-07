#ifndef PROJECT_SWA_ENTITYMOMENTO_H
#define PROJECT_SWA_ENTITYMOMENTO_H


class EntityMomento {
public:
    EntityMomento(int entityID);
    int getState() const;
private:
    int _entityId;
};


#endif //PROJECT_SWA_ENTITYMOMENTO_H

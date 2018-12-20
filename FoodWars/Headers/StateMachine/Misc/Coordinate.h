#ifndef PROJECT_SWA_COORDINATE_H
#define PROJECT_SWA_COORDINATE_H

#include "../../../../TonicEngine/Headers/Storage/SerializationReceiver.h"

class Coordinate : public SerializationReceiver {
public:
    Coordinate() : _xCoord{0}, _yCoord{0} {

    };
    ~Coordinate() = default;
public:
     int getXCoord() const;
     int getYCoord() const;
     const void setCoordinates(int x, int y);

    void accept(SerializationVisitor &visitor) override;

    std::string getName() const override;

private:
    int _xCoord;
    int _yCoord;
};


#endif //PROJECT_SWA_COORDINATE_H

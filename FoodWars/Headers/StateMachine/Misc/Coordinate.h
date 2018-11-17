#ifndef PROJECT_SWA_COORDINATE_H
#define PROJECT_SWA_COORDINATE_H


class Coordinate {
public:
    Coordinate() = default;
    ~Coordinate() = default;
public:
     int getXCoord() const;
     int getYCoord() const;
     const void setCoordinates(int x, int y);
private:
    int _xCoord;
    int _yCoord;
};


#endif //PROJECT_SWA_COORDINATE_H

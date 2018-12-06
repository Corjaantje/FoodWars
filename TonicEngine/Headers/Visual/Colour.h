#ifndef PROJECT_SWA_COLOUR_H
#define PROJECT_SWA_COLOUR_H


class Colour {
public:
    Colour(int red, int green, int blue, int alpha);
    ~Colour();
public:
    int red;
    int green;
    int blue;
    int alpha;

    virtual int getRed();

    virtual int getGreen();

    virtual int getBlue();

    virtual int getAlpha();
};


#endif //PROJECT_SWA_COLOUR_H

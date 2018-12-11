#ifndef PROJECT_SWA_COLOUR_H
#define PROJECT_SWA_COLOUR_H


#include "../Storage/SerializationReceiver.h"

class Colour : public SerializationReceiver {
public:
    Colour();
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

    void accept(SerializationVisitor &visitor) override;

    std::string getName() const override;
};


#endif //PROJECT_SWA_COLOUR_H

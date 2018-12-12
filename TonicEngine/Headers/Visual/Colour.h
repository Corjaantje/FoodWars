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

    int getRed();

    int getGreen();

    int getBlue();

    int getAlpha();

    void accept(SerializationVisitor &visitor) override;

    std::string getName() const override;
};


#endif //PROJECT_SWA_COLOUR_H

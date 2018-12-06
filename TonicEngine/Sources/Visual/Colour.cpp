#include "../../Headers/Visual/Colour.h"

Colour::Colour() : red{0}, green{0}, blue{0}, alpha{0} {

}

Colour::Colour(int red, int green, int blue, int alpha) : red(red), green(green), blue(blue), alpha(alpha) {

};

Colour::~Colour() = default;

void Colour::accept(SerializationVisitor &visitor) {
    visitor.visit("red", red);
    visitor.visit("green", green);
    visitor.visit("blue", blue);
    visitor.visit("alpha", alpha);
}

#include "../../Headers/Visual/Colour.h"

Colour::Colour(int red, int green, int blue, int alpha) : red(red), green(green), blue(blue), alpha(alpha) {
};

Colour::~Colour() = default;

int Colour::getRed() {
    return red;
}

int Colour::getGreen() {
    return green;
}

int Colour::getBlue() {
    return blue;
}

int Colour::getAlpha() {
    return alpha;
}

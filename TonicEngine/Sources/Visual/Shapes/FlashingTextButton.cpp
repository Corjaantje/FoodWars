
#include "../../../Headers/Visual/Shapes/FlashingTextButton.h"

FlashingTextButton::FlashingTextButton(MouseEventObservable& mouseEventObservable, const std::string& text, const std::function<void()>& onClick, int width, int height, int xPos, int yPos, Colour buttonColour, Colour textColour) :
    TextButton(mouseEventObservable, text, onClick, width, height, xPos, yPos), _flashing{true}{

}

void FlashingTextButton::setFlashColours(const std::vector<Colour> &colours) {
    _colours = colours;
}

void FlashingTextButton::addToRender(Renderlist *renderlist) {
    if (_flashing) {
        std::chrono::duration<double> currentTime = std::chrono::steady_clock::now().time_since_epoch();
        if (currentTime.count() - _timeLast.count() >= _interval) {
            _currentColourIndex += 1;
            if (_currentColourIndex >= _colours.size())
                _currentColourIndex = 0;
            _timeLast = currentTime;
        }
        shapeText.colour = _colours[_currentColourIndex];
    }
    TextButton::addToRender(renderlist);
}

void FlashingTextButton::setInterval(double intervalSec) {
    _interval = intervalSec;
}

void FlashingTextButton::setFlashing(bool val) {
    _flashing = val;
}

bool FlashingTextButton::getFlashing() const {
    return _flashing;
}


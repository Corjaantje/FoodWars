#ifndef PROJECT_SWA_FLASHINGSHAPINGTEXT_H
#define PROJECT_SWA_FLASHINGSHAPINGTEXT_H

#include "TextButton.h"
#include <chrono>

class FlashingTextButton : public TextButton {
private:
    std::chrono::duration<double> _timeLast = std::chrono::steady_clock::now().time_since_epoch();
    std::vector<Colour> _colours;
    int _currentColourIndex = 0;
    double _interval = 1;
    bool _flashing;
public:
    FlashingTextButton(MouseEventObservable& mouseEventObservable, const std::string& text, const std::function<void()>& onClick, int width, int height, int xPos, int yPos, Colour buttonColour, Colour textColour);
    void setInterval(double intervalMs);
    void setFlashColours(const std::vector<Colour>& colours);
    void addToRender(Renderlist* renderlist) override;
    void setFlashing(bool val);
    bool getFlashing() const;

};

#endif //PROJECT_SWA_FLASHINGSHAPINGTEXT_H

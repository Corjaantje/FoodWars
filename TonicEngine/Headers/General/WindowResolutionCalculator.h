#ifndef PROJECT_SWA_WINDOWRESOLUTIONCALCULATOR_H
#define PROJECT_SWA_WINDOWRESOLUTIONCALCULATOR_H


const float DEFAULT_WIDTH = 1600.00;
const float DEFAULT_HEIGHT = 900.00;

class WindowResolutionCalculator {
public:
    WindowResolutionCalculator();
    ~WindowResolutionCalculator() = default;
public:
    int getConvertedWidthDraw(int width);
    int getConvertedHeightDraw(int height);
    int getConvertedxPosDraw(int xPos);
    int getConvertedyPosDraw(int yPos);

    int getConvertedxPosClick(int xPos);
    int getConvertedyPosClick(int yPos);
    void setResolution(int width, int height);
private:
    int _windowWidth;
    int _windowHeight;
};


#endif //PROJECT_SWA_WINDOWRESOLUTIONCALCULATOR_H

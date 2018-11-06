#ifndef PROJECT_SWA_WINDOWRESOLUTIONCALCULATOR_H
#define PROJECT_SWA_WINDOWRESOLUTIONCALCULATOR_H


const float DEFAULT_WIDTH = 1600.00;
const float DEFAULT_HEIGHT = 900.00;

class WindowResolutionCalculator {
public:
    WindowResolutionCalculator();
    ~WindowResolutionCalculator() = default;
public:
    int getConvertedWidth(int width);
    int getConvertedHeight(int height);
    int getConvertedxPos(int xPos);
    int getConvertedyPos(int yPos);
    void setResolution(int width, int height);
private:
    int _windowWidth;
    int _windowHeight;
};


#endif //PROJECT_SWA_WINDOWRESOLUTIONCALCULATOR_H

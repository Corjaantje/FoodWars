#include <utility>

#include "../../Headers/Visual/WindowManager.h"
#include "../../Headers/Visual/Window.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <algorithm>

WindowManager::WindowManager(std::shared_ptr<WindowResolutionCalculator> windowResCalc) {
    _window = new Window(_title, _windowWidth, _windowHeight);
    _windowResCalc = std::move(windowResCalc);
    _assetManager = new AssetManager();
}

WindowManager::~WindowManager() {
    closeWindow();
    delete _window;
    delete _assetManager;
}

void WindowManager::openWindow(){
    _window->createWindow();
}

void WindowManager::closeWindow(){
    _window->closeWindow();
};

void WindowManager::setTitle(const std::string &title){
    _title = title;
    _window->setTitle(title);
};

void WindowManager::setResolution(int width, int height){
    _windowWidth = width;
    _windowHeight = height;
    _window->setResolution(width, height);
};

void WindowManager::enableFullscreen(){
    _fullscreen = true;
    _window->setFullscreen(true);
};

void WindowManager::disablefullscreen(){
    _fullscreen = false;
    _window->setFullscreen(false);
};

//(re)Draw all the shapes, sprites etc. that are added to the WindowManager
void WindowManager::render(Renderlist renderlist) {
    SDL_RenderClear(_renderer);
    _renderer = _window->getRenderer();

    // Sort the list by layer ascending
    quickSort(renderlist.rectangleList, 0, renderlist.rectangleList.size() - 1);

    // Add the sorted shapelist to queue
    //std::queue<ShapeRectangle> queue;
    //queue.push(renderlist.rectangleList[i]);
    renderRectangles(renderlist.rectangleList);
    renderSprites(renderlist.spriteList);
    renderText(renderlist.textList);
    SDL_RenderPresent(_renderer);
}

void WindowManager::swap (ShapeRectangle &a,ShapeRectangle &b){
    ShapeRectangle temp = a;
    a = b;             // a/b refer to the parameters that were passed
    b = temp;          // modifying a reference is the same as modifiying the original
}

int WindowManager::partition (std::vector<ShapeRectangle> rectangles, int low, int high)
{
    int pivot = rectangles[high].layer;    // pivot
    int i = (low - 1);  // Index of smaller element

    for (int j = low; j <= high- 1; j++)
    {
        // If current element is smaller than or
        // equal to pivot
        if (rectangles[j].layer <= pivot)
        {
            i++;    // increment index of smaller element
            swap(rectangles[i],rectangles[j]);
        }
    }
    swap(rectangles[i + 1], rectangles[high]);
    return (i + 1);
}

void WindowManager::quickSort(std::vector<ShapeRectangle> rectangles, int low, int high)
{
    if (low < high)
    {
        /* pi is partitioning index, arr[p] is now
           at right place */
        int pi = partition(rectangles, low, high);

        // Separately sort elements before
        // partition and after partition
        quickSort(rectangles, low, pi - 1);
        quickSort(rectangles, pi + 1, high);
    }
}

void WindowManager::renderRectangles(std::vector<ShapeRectangle> rectangleList) {
    for(int i=0; i< rectangleList.size(); i++){
        ShapeRectangle &rectangleShape = rectangleList[i];
        SDL_Rect rect;
        rect.x = _windowResCalc->getConvertedxPosDraw(rectangleShape.xPos);
        rect.y = _windowResCalc->getConvertedyPosDraw(rectangleShape.yPos);
        rect.h = _windowResCalc->getConvertedHeightDraw(rectangleShape.height);
        rect.w = _windowResCalc->getConvertedWidthDraw(rectangleShape.width);
        SDL_SetRenderDrawColor(_renderer, rectangleShape.colour.red, rectangleShape.colour.green, rectangleShape.colour.blue, rectangleShape.colour.alpha);
        SDL_RenderFillRect(_renderer, &rect);
    }
    SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 0);
}

void WindowManager::renderSprites(std::vector<ShapeSprite> rectangleSprite) {
    for(int i=0; i< rectangleSprite.size(); i++){
        ShapeSprite &shapeSprite = rectangleSprite[i];
        SDL_Rect rect;
        rect.x = _windowResCalc->getConvertedxPosDraw(shapeSprite.xPos);
        rect.y = _windowResCalc->getConvertedyPosDraw(shapeSprite.yPos);
        rect.h = _windowResCalc->getConvertedHeightDraw(shapeSprite.height);
        rect.w = _windowResCalc->getConvertedWidthDraw(shapeSprite.width);
        SDL_Texture* texture = _assetManager->GetSDLTextureFromPNG(_renderer, shapeSprite.imageURL);
        SDL_RenderCopy(_renderer, texture, NULL, &rect);
    }
}

void WindowManager::renderText(std::vector<ShapeText> textList) {
    for(int i=0; i< textList.size(); i++){
        ShapeText &shapeText = textList[i];
        SDL_Texture* Message = _assetManager->GetSDLTextureFromText(_renderer, shapeText);
        SDL_Rect Message_rect; //create a rect
        Message_rect.x = shapeText.xPos * (_windowWidth / DEFAULT_WIDTH);  //controls the rect's x coordinate
        Message_rect.y = shapeText.yPos * (_windowHeight / DEFAULT_HEIGHT); // controls the rect's y coordinte
        Message_rect.w = shapeText.width * (_windowHeight / DEFAULT_HEIGHT) + 1; // controls the width of the rect
        Message_rect.h = shapeText.height * (_windowWidth / DEFAULT_WIDTH) + 1; // controls the height of the rect
        SDL_RenderCopy(_renderer, Message, NULL, &Message_rect);
    }
}

void WindowManager::pollEvents() {
    _window->pollEvents();
}

bool WindowManager::isWindowClosed() {
    return _window->isClosed();
}

#ifndef PROJECT_SWA_FONTMANAGER_H
#define PROJECT_SWA_FONTMANAGER_H


#include <SDL2/SDL_render.h>
#include <map>
#include <SDL2/SDL_ttf.h>
#include "Shapes/ShapeText.h"

class FontManager {
public:
    FontManager() = default;
    ~FontManager() = default;
public:
    SDL_Texture* GetSDLTextureFromText(SDL_Renderer* renderer, ShapeText text);
private:
    std::map<std::string, SDL_Texture*> _textureMap;

};


#endif //PROJECT_SWA_FONTMANAGER_H

#ifndef PROJECT_SWA_ASSETMANAGER_H
#define PROJECT_SWA_ASSETMANAGER_H

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <map>
#include "Shapes/ShapeText.h"

class AssetManager {
public:
    AssetManager();
    ~AssetManager() = default;
public:
    SDL_Texture* GetSDLTextureFromText(SDL_Renderer* renderer, ShapeText text);
    SDL_Texture* GetSDLTextureFromPNG(SDL_Renderer* renderer, std::string fileName);
    SDL_Texture* GetSDLTextureFromBMP(SDL_Renderer* renderer, std::string fileName);
private:
    void FindAssets(std::string path);
    void LoadFonts(std::string fileName, std::string path);
    void LoadPNGs(std::string fileName, std::string path);
    void LoadBMPs(std::string fileName, std::string path);
private:
    std::map<std::string, TTF_Font*> _dictionaryFonts;

    std::map<std::string, SDL_Surface*> _surfaceMapPNG;
    std::map<std::string, SDL_Surface*> _surfaceMapBMP;

    std::map<std::string, SDL_Texture*> _textureMapText;
    std::map<std::string, SDL_Texture*> _textureMapPNG;
    std::map<std::string, SDL_Texture*> _textureMapBMP;

};


#endif //PROJECT_SWA_ASSETMANAGER_H

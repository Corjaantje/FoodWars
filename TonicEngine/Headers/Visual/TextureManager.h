#ifndef PROJECT_SWA_TEXTUREMANAGER_H
#define PROJECT_SWA_TEXTUREMANAGER_H


#include <SDL2/SDL_render.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <map>

class TextureManager {
public:
    TextureManager() = default;
    ~TextureManager() = default;
public:
    SDL_Texture* GetSDLTextureFromBMP(SDL_Renderer* renderer, std::string URL);
    SDL_Texture* GetSDLTextureFromPNG(SDL_Renderer* renderer, std::string URL);

private:
    std::map<std::string, SDL_Texture*> _textureMap;
};


#endif //PROJECT_SWA_TEXTUREMANAGER_H

#include "../../Headers/Visual/TextureManager.h"

SDL_Texture* TextureManager::GetSDLTextureFromBMP(SDL_Renderer* renderer, std::string URL) {
    if(_textureMap.count(URL) > 0){
        return _textureMap[URL];
    }
    else{
        SDL_Surface * image = SDL_LoadBMP(URL.c_str());
        SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, image);
        _textureMap[URL] = texture;
        return texture;
    }
}
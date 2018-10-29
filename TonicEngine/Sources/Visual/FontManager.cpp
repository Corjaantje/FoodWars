#include "../../Headers/Visual/FontManager.h"

SDL_Texture* FontManager::GetSDLTextureFromText(SDL_Renderer *renderer, ShapeText text) {
    if(_textureMap.count(text.toString()) == 0){
        TTF_Font* motion = TTF_OpenFont("../FoodWars/Assets/LDFComicSans.ttf", text.fontSize);
        SDL_Color Colour = {static_cast<Uint8>(text.colour.red), static_cast<Uint8>(text.colour.green),
                            static_cast<Uint8>(text.colour.blue)};
        SDL_Surface* surfaceMessage = TTF_RenderText_Solid(motion, text.text.c_str(), Colour);
        SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
        _textureMap[text.toString()] = Message;
        return Message;
    }
    else{
        return _textureMap[text.toString()];
    }
}
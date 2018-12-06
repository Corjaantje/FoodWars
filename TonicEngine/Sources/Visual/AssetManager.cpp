#include <dirent.h>
#include <iostream>
#include <sys/stat.h>
#include "../../Headers/Visual/AssetManager.h"

AssetManager::AssetManager() {
    this->FindAssets("./Assets/");
}

SDL_Texture* AssetManager::GetSDLTextureFromPNG(SDL_Renderer *renderer, std::string fileName) {
    if(_surfaceMapPNG.count(fileName) == 0){
        return nullptr;
    }

    if(_textureMapPNG.count(fileName) > 0){
        return _textureMapPNG[fileName];
    }
    else{
        SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, _surfaceMapPNG[fileName]);
        _textureMapPNG[fileName] = texture;
        return texture;
    }
}

SDL_Texture* AssetManager::GetSDLTextureFromBMP(SDL_Renderer* renderer, std::string fileName) {
    if(_surfaceMapBMP.count(fileName) == 0){
        return nullptr;
    }

    if(_textureMapBMP.count(fileName) > 0){
        return _textureMapBMP[fileName];
    }
    else{
        SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, _surfaceMapBMP[fileName]);
        _textureMapBMP[fileName] = texture;
        return texture;
    }
}

SDL_Texture* AssetManager::GetSDLTextureFromText(SDL_Renderer *renderer, ShapeText text) {
    if(_textureMapText.count(text.toString()) == 0){
        SDL_Color Colour;
        Colour.r = (uint8_t) text.colour.getRed();
        Colour.g = (uint8_t) text.colour.getGreen();
        Colour.b = (uint8_t) text.colour.getBlue();
        Colour.a = (uint8_t) text.colour.getAlpha();

        SDL_Surface* surfaceMessage = TTF_RenderText_Solid(_dictionaryFonts["PopularCafeNF.ttf"], text.text.c_str(), Colour);
        SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
        _textureMapText[text.toString()] = Message;
        return Message;
    }
    else{
        return _textureMapText[text.toString()];
    }
}

void AssetManager::FindAssets(std::string dir_name) {
  DIR *dir;
  struct dirent *entry;
  struct stat info;

  dir = opendir(dir_name.c_str());
  if(!dir){
      return;
  }

  while((entry = readdir(dir)) != nullptr){
      if(entry->d_name[0] != '.'){
          std::string path = std::string(dir_name) + "/" + std::string(entry->d_name);
          stat(path.c_str(),&info);
          if(S_ISDIR(info.st_mode)){
              this->FindAssets(path);
          }
          else{
              if(path.find(".png") != std::string::npos){
                  this->LoadPNGs(entry->d_name, path);
              }
              else if(path.find(".bmp") != std::string::npos){
                  this->LoadBMPs(entry->d_name,path);
              }
              else if(path.find(".ttf") != std::string::npos){
                    this->LoadFonts(entry->d_name,path);
              }
          }
      }
  };
  closedir(dir);
}

void AssetManager::LoadFonts(std::string fileName, std::string path) {
    std::cout << "Loading Font " << fileName << "\n";
    try {
        TTF_Font *font = TTF_OpenFont(path.c_str(), 150);
        _dictionaryFonts[fileName] = font;
    }
    catch(std::exception& e){
        std::cerr << "Could not find font!";
    }
}

void AssetManager::LoadBMPs(std::string fileName, std::string path) {
    std::cout << "BMP = " << fileName << "\n";
    SDL_Surface * image = SDL_LoadBMP(path.c_str());
    _surfaceMapPNG[fileName] = image;
}

void AssetManager::LoadPNGs(std::string fileName, std::string path) {
    std::cout << "Loading Image " << fileName << "\n";
    SDL_Surface * image = IMG_Load(path.c_str());
    _surfaceMapPNG[fileName] = image;
}
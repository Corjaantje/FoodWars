#include <iostream>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "../../Headers/Visual/Window.h"

Window::Window(const std::string &title, int width, int height) : _title(title), _width(width), _height(height)
{
    if(!init()){
        _closed = true;
    }
}

Window::~Window()
{
    SDL_DestroyWindow(_window);
    SDL_Quit();
}

bool Window::init(){
    if(SDL_Init(SDL_INIT_VIDEO) != 0){
        std::cerr << "Failed to initialize SDL.\n";
        return 0;
    }
    if(TTF_Init() != 0){
        return 0;
    }
    if(IMG_Init(IMG_INIT_PNG) != 0){
        return 0;
    }
    return true;
};

//Handle the Quit event on the window. Will be replaced/improved by a Observable based event handler.
void Window::pollEvents(){
    SDL_Event event;
    if(SDL_PollEvent(&event)){
        switch(event.type){
            case SDL_QUIT:
                _closed = true;
                break;

            default:
                break;
        }
    }
}

//TODO Find a better way to dynamically set more Window Flag settings
bool Window::createWindow() {
    auto _flags = SDL_WINDOW_RESIZABLE;
    if(_fullscreen) {
        _flags = SDL_WINDOW_FULLSCREEN;
    }
        _window = SDL_CreateWindow(
                _title.c_str(),
                SDL_WINDOWPOS_CENTERED,
                SDL_WINDOWPOS_CENTERED,
                _width,
                _height,
                _flags);
    _closed = false;
        if(_window == nullptr) {
            std::cerr << "Failed to create window.\n";
            return 0;
        }
        else{
            _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
        }
}

bool Window::closeWindow() {
    if(!_closed)
        SDL_DestroyWindow(_window);
    _closed = true;
}

bool Window::setFullscreen(bool state) {
    _fullscreen = state;
    SDL_SetWindowFullscreen(_window, state);
}

SDL_Renderer* Window::getRenderer() {
    return _renderer;
}

void Window::setTitle(const std::string &title){
    _title = title;
    SDL_SetWindowTitle(_window, &title[0]);
};

void Window::setResolution(int width, int height){
    _width = width;
    _height = height;
    SDL_SetWindowSize(_window, width, height);
};

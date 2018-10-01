#include <iostream>
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

    _window = SDL_CreateWindow(
            _title.c_str(),
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            _width,
            _height,
            0);

    if(_window == nullptr){
        std::cerr << "Failed to create window.\n";
        return 0;
    }
    return true;
};

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
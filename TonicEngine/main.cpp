#include "Window.h"
int main(int argc, char** argv)
{
    Window window("SDL Window", 640, 480);

    while(!window.isClosed()){
        window.pollEvents();
    }
    return 0;
}

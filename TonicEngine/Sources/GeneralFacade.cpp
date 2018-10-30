#include <SDL2/SDL_timer.h>
#include "../Facades/GeneralFacade.h"

GeneralFacade::GeneralFacade() = default;

GeneralFacade::~GeneralFacade() = default;

void GeneralFacade::sleep(int millis) const {
    SDL_Delay(static_cast<Uint32>(millis));
}
#ifndef TIME_H
#define TIME_H

#pragma once

#include <SDL2/SDL.h>

namespace Time{
    static float deltaTime(float &lastTime){
        Uint32 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;

        return deltaTime;
    }
}

#endif
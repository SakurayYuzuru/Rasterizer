#ifndef WINDOW_H
#define WINDOW_H

#pragma once

#include <SDL2/SDL.h>

class Window{
public:
    static const int HEIGHT = 960, WIDTH = 720;

    Window();
    ~Window();

    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;

private:   
    int w, l;
};

#endif
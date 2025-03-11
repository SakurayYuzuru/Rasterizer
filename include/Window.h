#ifndef WINDOW_H
#define WINDOW_H

#pragma once

#include <SDL2/SDL.h>

class Window{
public:
    Window();
    ~Window();

    SDL_Window* GetWindow() const;
    SDL_Renderer* GetRenderer() const;
    SDL_Texture* GetTexture() const;

    int width() const;
    int height() const;

private:   
    int w, h;
    static const int HEIGHT = 960, WIDTH = 1080;

    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;
};

#endif
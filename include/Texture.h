#ifndef TEXTURE_H
#define TEXTURE_H

#pragma once

#include <SDL2/SDL.h>

class Texture{
public:
    Texture();
    ~Texture();

    void loadTexture(SDL_Renderer* renderer, const char* path);
    void render(SDL_Renderer* renderer, int x, int y, int width, int height);
    void clear();

    SDL_Texture* getTexture() const;

private:
    SDL_Texture *texture;
};

#endif
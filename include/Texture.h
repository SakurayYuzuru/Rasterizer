#ifndef TEXTURE_H
#define TEXTURE_H

#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <Color.h>
#include <Math.h>

#include <vector>
#include <string>

class Texture{
public:
    Texture();
    Texture(const std::string& path);
    ~Texture();

    void LoadTexture(const std::string& path);
    
    int width() const;
    int height() const;

    Color GetColor(float u, float v);
    Color GetColor(Math::Vector2f uv);

private:
    SDL_Surface* texture;
};

#endif
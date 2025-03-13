#ifndef TEXTURE_H
#define TEXTURE_H

#pragma once

#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>

#include <string>

struct Image{
    int width, height;
    Uint32* pixel;
};

class Texture{
public:
    Texture(const std::string& path);
    ~Texture();
    void LoadTexture(const std::string& path);
    Image GetImage() const;
private:
    Image img;
};

#endif
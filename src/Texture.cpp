#include <Texture.h>
#include <iostream>

Texture::Texture() : format(nullptr){ }
Texture::Texture(const std::string& path) : format(nullptr){
    LoadTexture(path);
}
Texture::~Texture(){
    IMG_Quit();
    delete []img.pixel;
}

void Texture::LoadTexture(const std::string& path){
    SDL_Surface* surface = IMG_Load(path.c_str());

    if(!surface){
        std::cerr << "IMAGE::LOAD::ERROR: " << IMG_GetError() << std::endl;
        return ;
    }

    this->format = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_RGBA32, 0);
    SDL_FreeSurface(surface);
    if(!format){
        std::cerr << "SURFACE::CONVERT::ERROR: " << SDL_GetError() << std::endl;
        return ;
    }

    img.height = format->h;
    img.width = format->w;
    img.pixel = new Uint32[img.height * img.width];
    memcpy(img.pixel, format->pixels, img.height * img.width * sizeof(Uint32));
    SDL_FreeSurface(format);
}

Image Texture::GetImage() const{
    return this->img;
}
SDL_Surface* Texture::GetSurface() const{
    return this->format;
}
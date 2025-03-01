#include <Texture.h>
#include <iostream>
#include <SDL2/SDL_image.h>

Texture::Texture() : texture(nullptr) { }
Texture::~Texture() {
    delete this->texture;
}

void Texture::loadTexture(SDL_Renderer* renderer, const char* path){
    SDL_Surface* surface = IMG_Load(path);
    if(!surface){
        std::cerr << "ERROR::SURFACE::INIT: " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    this->texture = SDL_CreateTextureFromSurface(renderer, surface);
    if(this->texture == nullptr){
        std::cerr << "SDL::TEXTURE::CREATE::ERROR: " << SDL_GetError() << std::endl;
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
}

void Texture::render(SDL_Renderer* renderer, int x, int y, int width, int height){
    SDL_Rect rect = {x, y, width, height};
    SDL_RenderCopy(renderer, this->texture, nullptr, &rect);
}

void Texture::clear(){
    if (this->texture) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
}

SDL_Texture* Texture::getTexture() const{
    return this->texture;
}
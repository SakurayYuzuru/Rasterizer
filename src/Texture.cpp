#include <Texture.h>
#include <iostream>
#include <algorithm>

Texture::Texture() : texture(nullptr) { }
Texture::Texture(const std::string& path) : texture(nullptr) {
    LoadTexture(path);
}
Texture::~Texture(){ }

void Texture::LoadTexture(const std::string& path){
    SDL_Surface* surface = IMG_Load(path.c_str());
    if(!surface){
        std::cerr << "Invalid Texture Path" << std::endl;
        return ;
    }

    this->texture = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_ARGB8888, 0);
    SDL_FreeSurface(surface);
}

int Texture::width() const{
    return texture->w;
}
int Texture::height() const{
    return texture->h;
}

Color Texture::GetColor(float u, float v){
    u = std::clamp(u, 0.0f, 1.0f);
    v = std::clamp(v, 0.0f, 1.0f);

    auto u_img = static_cast<int>(u * (texture->w - 1));
    auto v_img = static_cast<int>(v * (texture->h - 1));

    Uint32* pixels = (Uint32*)texture->pixels;
    uint32_t color = pixels[v_img * texture->w + u_img];
    Uint8 ur, ug, ub, ua;
    SDL_GetRGBA(color, texture->format, &ur, &ug, &ub, &ua);
    float r = ur / 255.0f, g = ug / 255.0f, b = ub / 255.0f, a = ua / 255.0f;
    return {r, g, b, a};
}
Color Texture::GetColor(Math::Vector2f uv){
    float u = std::clamp(uv.x, 0.0f, 1.0f);
    float v = std::clamp(uv.y, 0.0f, 1.0f);

    auto u_img = static_cast<int>(u * (texture->w - 1));
    auto v_img = static_cast<int>(v * (texture->h - 1));

    Uint32* pixels = (Uint32*)texture->pixels;
    uint32_t color = pixels[v_img * texture->w + u_img];
    Uint8 ur, ug, ub, ua;
    SDL_GetRGBA(color, texture->format, &ur, &ug, &ub, &ua);
    float r = ur / 255.0f, g = ug / 255.0f, b = ub / 255.0f, a = ua / 255.0f;

    return {r, g, b, a};
}
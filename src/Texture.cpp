#include <Texture.h>
#include <iostream>

Texture::Texture(){ }
Texture::Texture(const std::string& path){
    LoadTexture(path);
}
Texture::~Texture(){
    IMG_Quit();
}

void Texture::LoadTexture(const std::string& path){
    SDL_Surface* surface = IMG_Load(path.c_str());

    if(!surface){
        std::cerr << "IMAGE::LOAD::ERROR: " << IMG_GetError() << std::endl;
        return ;
    }

    SDL_Surface* format = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_RGBA32, 0);
    SDL_FreeSurface(surface);
    if(!format){
        std::cerr << "SURFACE::CONVERT::ERROR: " << SDL_GetError() << std::endl;
        return ;
    }

    this->w = format->w;
    this->h = format->h;

    Uint32* pixels = static_cast<Uint32*>(format->pixels);

    for(int y = 0; y < h; ++ y){
        for(int x = 0; x < w; ++ x){
            Uint32 pixel = pixels[y * w + x];
            Uint8 r, g, b, a;
            SDL_GetRGBA(pixel, format->format, &r, &g, &b, &a);
            this->img[y][x] = Color(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
        }
    }
}

int Texture::width() const{
    return this->w;
}
int Texture::height() const{
    return this->h;
}

Color Texture::GetColor(float u, float v){
    if(u < 0.0f){
        u = 0.0f;
    }
    if(u > 1.0f){
        u = 1.0f;
    }
    if(v < 0.0f){
        v = 0.0f;
    }
    if(v > 1.0f){
        v = 1.0f;
    }

    auto u_img = u * this->w;
    auto v_img = (1 - v) * this->h;

    auto color = this->img[v_img][u_img];
    return color;
}
Color Texture::GetColor(Math::Vector2f uv){
    float u = uv.x;
    float v = uv.y;

    return GetColor(u, v);
}
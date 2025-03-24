#include <Texture.h>
#include <iostream>

Texture::Texture(){ }
Texture::Texture(const std::string& path){
    LoadTexture(path);
}
Texture::~Texture(){ }

void Texture::LoadTexture(const std::string& path){
    int npComponents;
    unsigned char *data = stbi_load(path.c_str(), &this->h, &this->w, &npComponents, 0);
    if(!data){
        std::cerr << "Texture::Load::Error" << std::endl;
        stbi_image_free(data);
        return ;
    }

    this->img.resize(this->h, std::vector<Color>(this->w));
    for(int y = 0; y < this->h; ++ y){
        for(int x = 0; x < this->w; ++ x){
            int index = (y * this->w + x) * npComponents;
            float r = data[index] / 255.0f;
            float g = data[index + 1] / 255.0f;
            float b = data[index + 2] / 255.0f;
            float a = npComponents == 4 ? data[index + 3] / 255.0f : 1.0f;

            this->img[y][x] = Color(r, g, b, a);
            // std::cout << r << " " << g << " " << b << std::endl;
        }
    }

    stbi_image_free(data);
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
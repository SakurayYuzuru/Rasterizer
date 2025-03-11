#include <Window.h>
#include <iostream>

Window::Window() : h(HEIGHT), w(WIDTH){
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        std::cerr << "SDL::INIT::ERROR: " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    this->window = SDL_CreateWindow("SRasterizer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->h, this->w, SDL_WINDOW_SHOWN);
    if(this->window == nullptr){
        std::cerr << "SDL::WINDOW::CREATE::ERROR: " << SDL_GetError() << std::endl;
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);
    if(this->renderer == nullptr){
        std::cerr << "SDL::RENDERER::CREATE::ERROR: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(this->window);
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    this->texture = SDL_CreateTexture(this->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, this->HEIGHT, this->WIDTH);
    if(this->texture == nullptr){
        std::cerr << "SDL::TEXTURE::CREATE::ERROR: " << SDL_GetError() << std::endl;
        SDL_DestroyRenderer(this->renderer);
        SDL_DestroyWindow(this->window);
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
}

Window::~Window(){
    SDL_DestroyTexture(this->texture);
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    SDL_Quit();
}

int Window::height() const{
    return this->h;
}
int Window::width() const{
    return this->w;
}

SDL_Window* Window::GetWindow() const{
    return this->window;
}
SDL_Renderer* Window::GetRenderer() const{
    return this->renderer;
}
SDL_Texture* Window::GetTexture() const{
    return this->texture;
}
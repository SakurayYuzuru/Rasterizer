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
}

Window::~Window(){
    delete this->texture;
    delete this->renderer;
    delete this->window;
}

int Window::height() const{
    return this->h;
}
int Window::width() const{
    return this->w;
}

SDL_Window* Window::getWindow() const{
    return this->window;
}
SDL_Renderer* Window::getRenderer() const{
    return this->renderer;
}
SDL_Texture* Window::getTexture() const{
    return this->texture;
}
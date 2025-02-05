#include <Rasterizer.h>
#include <iostream>
#include <cstdlib>

Rasterizer::Rasterizer(){ }
Rasterizer::Rasterizer(Window _window) : window(_window){ }

Rasterizer::~Rasterizer(){ }

// Bresen Ham's algorithm
void Rasterizer::drawLine(Vector3f &begin, Vector3f &end){
    auto x1 = begin.x, y1 = begin.y;
    auto x2 = end.x, y2 = end.y;

    Vector4f line_color(255.0f, 0.0f, 0.0f, 255.0f);
    SDL_SetRenderDrawColor(this->window.renderer, line_color.x, line_color.y, line_color.z, line_color.w);

    int ox = x2 - x1;
    int oy = y2 - y1;
    int dx = std::fabs(ox);
    int dy = std::fabs(oy);
    int px = 2 * dy - dx;
    int py = 2 * dx - dy;
    int twoDy = 2 * dy, twoDyMinusDx = 2 * (dy - dx);
    int twoDx = 2 * dx, twoDxMinusDy = 2 * (dx - dy);
    int x, y;

    if(dy <= dx){
        if(x1 > x2){
            x = x2;
            y = y2;
            x2 = x1;
        }else{
            x = x1;
            y = y1;
        }

        Vector3f point(x, y, 1.0f);
        SDL_RenderDrawPoint(this->window.renderer, point.x, point.y);

        while(x < x2){
            x ++;
            if(px < 0){
                px += twoDy;
            }else{
                if((ox > 0 && oy > 0) || (ox < 0 && oy < 0)){
                    y ++;
                }else{
                    y --;
                }
                px += twoDyMinusDx;
            }
            point = Vector3f(x, y, 1.0f);
            SDL_RenderDrawPoint(this->window.renderer, point.x, point.y);
        }
    }else{
        if(y1 > y2){
            y = y2;
            x = x2;
            y2 = y1;
        }else{
            y = y1;
            x = x1;
        }

        Vector3f point(x, y, 1.0f);
        SDL_RenderDrawPoint(this->window.renderer, point.x, point.y);

        while(y < y2){
            y ++;
            if(py < 0){
                py += twoDx;
            }else{
                if((ox > 0 && oy > 0) || (ox < 0 && oy < 0)){
                    x ++;
                }else{
                    x --;
                }
                py += twoDxMinusDy;
            }
            point = Vector3f(x, y, 1.0f);
            SDL_RenderDrawPoint(this->window.renderer, point.x, point.y);
        }
    }
}

void Rasterizer::draw(){
    bool quit = false;
    SDL_Event e;

    while(!quit){
        while(SDL_PollEvent(&e) != 0){
            if(e.type == SDL_QUIT){
                quit = true;
            }
        }

        Vector4f background_color(0.0f, 0.0f, 0.0f, 255.0f);
        SDL_SetRenderDrawColor(this->window.renderer, background_color.x, background_color.y, background_color.z, background_color.w);
        SDL_RenderClear(this->window.renderer);
        Vector3f start(1.0f, 2.0f, 3.0f);
        Vector3f end(3.0f, 4.0f, 3.0f);
        //drawLine(start, end);
        SDL_RenderDrawLine(this->window.renderer, start.x, start.y, end.x, end.y);
        SDL_RenderPresent(this->window.renderer);
    }

    SDL_DestroyRenderer(this->window.renderer);
    SDL_DestroyWindow(this->window.window);
    SDL_Quit();
}
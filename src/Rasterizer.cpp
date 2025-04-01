#include <Rasterizer.h>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <Shader.h>

Rasterizer::Rasterizer(){
    Start();
}
Rasterizer::~Rasterizer(){
    Destroy();
}

Rasterizer& Rasterizer::GetInstance(){
    static Rasterizer rst;
    return rst;
}

void Rasterizer::Start(){
    this->mesh = nullptr;
    this->model_angle = 1.0f;
    this->deltaTime = 0.0f;
    this->lastTime = 0.0f;
    this->frame_count = 0;
    this->quit = false;
    this->frame_buf.resize(this->window.height() * this->window.width());
    this->z_buffer.resize(this->window.height() * this->window.width(), -std::numeric_limits<float>::infinity());
    this->fragment_shader = Shader::phong_fragment_shader;
    this->texture = std::nullopt;
}
void Rasterizer::Update(){
    draw();
}
void Rasterizer::Destroy(){  }

void Rasterizer::Execute(){
    while(!this->quit){
        Update();
    }
}

// Show features
void Rasterizer::ShowBresen(){
    while(!this->quit){
        while(SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT){
                this->quit = true;
            }
            if(e.key.keysym.sym == SDLK_ESCAPE){
                this->quit = true;
            }
        }
    
        Math::Vector4f background_color(0.0f, 0.0f, 0.0f, 255.0f);
        SDL_SetRenderDrawColor(this->window.GetRenderer(), background_color.x, background_color.y, background_color.z, background_color.w);
        
        clear();
    
        Triangle t;
        t.setVertex(0, Math::Vector3f(540.0f, 320.0f, 0.0f));
        t.setVertex(1, Math::Vector3f(270.0f, 640.0f, 0.0f));
        t.setVertex(2, Math::Vector3f(810.0f, 640.0f, 0.0f));
    
        drawTriangle(t);
        RenderCopy();
    }
}
void Rasterizer::ShowRst(){
    while(!this->quit){
        while(SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT){
                this->quit = true;
            }
            if(e.type == SDL_KEYDOWN){
                processInput();
            }
        }

        Math::Vector4f background_color(0.0f, 0.0f, 0.0f, 255.0f);
        SDL_SetRenderDrawColor(this->window.GetRenderer(), background_color.x, background_color.y, background_color.z, background_color.w);
            
        clear();

        Triangle t;
        t.setVertex(0, Math::Vector3f(540.0f, 320.0f, 0.0f));
        t.setVertex(1, Math::Vector3f(270.0f, 640.0f, 0.0f));
        t.setVertex(2, Math::Vector3f(810.0f, 640.0f, 0.0f));
        t.setColor(0, 1.0f, 0.0f, 0.0f);
        t.setColor(1, 0.0f, 1.0f, 0.0f);
        t.setColor(2, 0.0f, 0.0f, 1.0f);
    
        triangleRasterize(t);
        RenderCopy();
    }
}
void Rasterizer::ShowZBuffer(){
    while(!this->quit){
        while(SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT){
                this->quit = true;
            }
            if(e.type == SDL_KEYDOWN){
                processInput();
            }
        }

        Math::Vector4f background_color(0.0f, 0.0f, 0.0f, 255.0f);
        SDL_SetRenderDrawColor(this->window.GetRenderer(), background_color.x, background_color.y, background_color.z, background_color.w);
        
        clear();

        Triangle triangle1, triangle2;
        triangle1.setVertex(0, Math::Vector3f(400.0f, 200.0f, 1.0f));
        triangle1.setVertex(1, Math::Vector3f(200.0f, 600.0f, 1.0f));
        triangle1.setVertex(2, Math::Vector3f(600.0f, 600.0f, 1.0f));
        triangle1.setColor(0, 0.0f, 1.0f, 0.0f);
        triangle1.setColor(1, 0.0f, 1.0f, 0.0f);
        triangle1.setColor(2, 0.0f, 1.0f, 0.0f);

        triangle2.setVertex(0, Math::Vector3f(300.0f, 300.0f, 5.0f));
        triangle2.setVertex(1, Math::Vector3f(265.0f, 665.0f, 5.0f));
        triangle2.setVertex(2, Math::Vector3f(665.0f, 665.0f, 5.0f));
        triangle2.setColor(0, 1.0f, 0.0f, 0.0f);
        triangle2.setColor(1, 1.0f, 0.0f, 0.0f);
        triangle2.setColor(2, 1.0f, 0.0f, 0.0f);

        triangleRasterize(triangle1);
        triangleRasterize(triangle2);
        RenderCopy();
    }
}
void Rasterizer::TestTexture(){
    Triangle t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12;
    // Z+
    t1.setVertex(0, Math::Vector3f(2.0f, -2.0f, 2.0f));
    t1.setVertex(1, Math::Vector3f(2.0f, 2.0f, 2.0f));
    t1.setVertex(2, Math::Vector3f(-2.0f, -2.0f, 2.0f));
    t2.setVertex(0, Math::Vector3f(-2.0f, 2.0f, 2.0f));
    t2.setVertex(1, Math::Vector3f(2.0f, 2.0f, 2.0f));
    t2.setVertex(2, Math::Vector3f(-2.0f, -2.0f, 2.0f));
    // Z-
    t3.setVertex(0, Math::Vector3f(2.0f, -2.0f, -2.0f));
    t3.setVertex(1, Math::Vector3f(2.0f, 2.0f, -2.0f));
    t3.setVertex(2, Math::Vector3f(-2.0f, -2.0f, -2.0f));
    t4.setVertex(0, Math::Vector3f(-2.0f, 2.0f, -2.0f));
    t4.setVertex(1, Math::Vector3f(2.0f, 2.0f, -2.0f));
    t4.setVertex(2, Math::Vector3f(-2.0f, -2.0f, -2.0f));
    // X+
    t5.setVertex(0, Math::Vector3f(2.0f, -2.0f, -2.0f));
    t5.setVertex(1, Math::Vector3f(2.0f, -2.0f, 2.0f));
    t5.setVertex(2, Math::Vector3f(2.0f, 2.0f, -2.0f));
    t6.setVertex(0, Math::Vector3f(2.0f, 2.0f, 2.0f));
    t6.setVertex(1, Math::Vector3f(2.0f, -2.0f, 2.0f));
    t6.setVertex(2, Math::Vector3f(2.0f, 2.0f, -2.0f));
    // X-
    t7.setVertex(0, Math::Vector3f(-2.0f, -2.0f, -2.0f));
    t7.setVertex(1, Math::Vector3f(-2.0f, -2.0f, 2.0f));
    t7.setVertex(2, Math::Vector3f(-2.0f, 2.0f, -2.0f));
    t8.setVertex(0, Math::Vector3f(-2.0f, 2.0f, 2.0f));
    t8.setVertex(1, Math::Vector3f(-2.0f, -2.0f, 2.0f));
    t8.setVertex(2, Math::Vector3f(-2.0f, 2.0f, -2.0f));
    // Y-
    t9.setVertex(0, Math::Vector3f(2.0f, -2.0f, 2.0f));
    t9.setVertex(1, Math::Vector3f(-2.0f, -2.0f, 2.0f));
    t9.setVertex(2, Math::Vector3f(2.0f, -2.0f, -2.0f));
    t10.setVertex(0, Math::Vector3f(-2.0f, -2.0f, -2.0f));
    t10.setVertex(1, Math::Vector3f(2.0f, -2.0f, 2.0f));
    t10.setVertex(2, Math::Vector3f(2.0f, -2.0f, -2.0f));
    // Y+
    t11.setVertex(0, Math::Vector3f(2.0f, 2.0f, 2.0f));
    t11.setVertex(1, Math::Vector3f(-2.0f, 2.0f, 2.0f));
    t11.setVertex(2, Math::Vector3f(2.0f, 2.0f, -2.0f));
    t12.setVertex(0, Math::Vector3f(-2.0f, 2.0f, -2.0f));
    t12.setVertex(1, Math::Vector3f(2.0f, 2.0f, 2.0f));
    t12.setVertex(2, Math::Vector3f(2.0f, 2.0f, -2.0f));

    // Z+
    t1.setNormal(0, Math::Vector3f(1.0f, 0.0f, 1.0f));
    t1.setNormal(1, Math::Vector3f(1.0f, 1.0f, 0.0f));
    t1.setNormal(2, Math::Vector3f(0.0f, 1.0f, 1.0f));
    t2.setNormal(0, Math::Vector3f(1.0f, 0.0f, 1.0f));
    t2.setNormal(1, Math::Vector3f(1.0f, 1.0f, 0.0f));
    t2.setNormal(2, Math::Vector3f(0.0f, 1.0f, 1.0f));
    // Z-
    t3.setNormal(0, Math::Vector3f(0.0f, 0.0f, -1.0f));
    t3.setNormal(1, Math::Vector3f(0.0f, 0.0f, -1.0f));
    t3.setNormal(2, Math::Vector3f(0.0f, 0.0f, -1.0f));
    t4.setNormal(0, Math::Vector3f(0.0f, 0.0f, -1.0f));
    t4.setNormal(1, Math::Vector3f(0.0f, 0.0f, -1.0f));
    t4.setNormal(2, Math::Vector3f(0.0f, 0.0f, -1.0f));
    // X+
    t5.setNormal(0, Math::Vector3f(1.0f, 0.0f, 0.0f));
    t5.setNormal(1, Math::Vector3f(1.0f, 0.0f, 0.0f));
    t5.setNormal(2, Math::Vector3f(1.0f, 0.0f, 0.0f));
    t6.setNormal(0, Math::Vector3f(1.0f, 0.0f, 0.0f));
    t6.setNormal(1, Math::Vector3f(1.0f, 0.0f, 0.0f));
    t6.setNormal(2, Math::Vector3f(1.0f, 0.0f, 0.0f));
    // X-
    t7.setNormal(0, Math::Vector3f(-1.0f, 0.0f, 0.0f));
    t7.setNormal(1, Math::Vector3f(-1.0f, 0.0f, 0.0f));
    t7.setNormal(2, Math::Vector3f(-1.0f, 0.0f, 0.0f));
    t8.setNormal(0, Math::Vector3f(-1.0f, 0.0f, 0.0f));
    t8.setNormal(1, Math::Vector3f(-1.0f, 0.0f, 0.0f));
    t8.setNormal(2, Math::Vector3f(-1.0f, 0.0f, 0.0f));
    // Y-
    t9.setNormal(0, Math::Vector3f(0.0f, -1.0f, 0.0f));
    t9.setNormal(1, Math::Vector3f(0.0f, -1.0f, 0.0f));
    t9.setNormal(2, Math::Vector3f(0.0f, -1.0f, 0.0f));
    t10.setNormal(0, Math::Vector3f(0.0f, -1.0f, 0.0f));
    t10.setNormal(1, Math::Vector3f(0.0f, -1.0f, 0.0f));
    t10.setNormal(2, Math::Vector3f(0.0f, -1.0f, 0.0f));
    // Y+
    t11.setNormal(0, Math::Vector3f(0.0f, 1.0f, 0.0f));
    t11.setNormal(1, Math::Vector3f(0.0f, 1.0f, 0.0f));
    t11.setNormal(2, Math::Vector3f(0.0f, 1.0f, 0.0f));
    t12.setNormal(0, Math::Vector3f(0.0f, 1.0f, 0.0f));
    t12.setNormal(1, Math::Vector3f(0.0f, 1.0f, 0.0f));
    t12.setNormal(2, Math::Vector3f(0.0f, 1.0f, 0.0f));

    t1.setColor(0, 1.0f, 1.0f, 0.0f);
    t1.setColor(1, 1.0f, 1.0f, 0.0f);
    t1.setColor(2, 1.0f, 1.0f, 0.0f);
    t2.setColor(0, 1.0f, 1.0f, 0.0f);
    t2.setColor(1, 1.0f, 1.0f, 0.0f);
    t2.setColor(2, 1.0f, 1.0f, 0.0f);

    t3.setColor(0, 1.0f, 1.0f, 0.0f);
    t3.setColor(1, 1.0f, 1.0f, 0.0f);
    t3.setColor(2, 1.0f, 1.0f, 0.0f);
    t4.setColor(0, 1.0f, 1.0f, 0.0f);
    t4.setColor(1, 1.0f, 1.0f, 0.0f);
    t4.setColor(2, 1.0f, 1.0f, 0.0f);

    t5.setColor(0, 1.0f, 0.0f, 1.0f);
    t5.setColor(1, 1.0f, 0.0f, 1.0f);
    t5.setColor(2, 1.0f, 0.0f, 1.0f);
    t6.setColor(0, 1.0f, 0.0f, 1.0f);
    t6.setColor(1, 1.0f, 0.0f, 1.0f);
    t6.setColor(2, 1.0f, 0.0f, 1.0f);

    t7.setColor(0, 1.0f, 0.0f, 1.0f);
    t7.setColor(1, 1.0f, 0.0f, 1.0f);
    t7.setColor(2, 1.0f, 0.0f, 1.0f);
    t8.setColor(0, 1.0f, 0.0f, 1.0f);
    t8.setColor(1, 1.0f, 0.0f, 1.0f);
    t8.setColor(2, 1.0f, 0.0f, 1.0f);

    t9.setColor(0, 0.0f, 1.0f, 1.0f);
    t9.setColor(1, 0.0f, 1.0f, 1.0f);
    t9.setColor(2, 0.0f, 1.0f, 1.0f);
    t10.setColor(0, 0.0f, 1.0f, 1.0f);
    t10.setColor(1, 0.0f, 1.0f, 1.0f);
    t10.setColor(2, 0.0f, 1.0f, 1.0f);

    t11.setColor(0, 0.0f, 1.0f, 1.0f);
    t11.setColor(1, 0.0f, 1.0f, 1.0f);
    t11.setColor(2, 0.0f, 1.0f, 1.0f);
    t12.setColor(0, 0.0f, 1.0f, 1.0f);
    t12.setColor(1, 0.0f, 1.0f, 1.0f);
    t12.setColor(2, 0.0f, 1.0f, 1.0f);

    t1.setTexture(0, 1.0f, 0.0f);
    t1.setTexture(1, 1.0f, 1.0f);
    t1.setTexture(2, 0.0f, 0.0f);
    t2.setTexture(0, 0.0f, 1.0f);
    t2.setTexture(1, 1.0f, 1.0f);
    t2.setTexture(2, 0.0f, 0.0f);

    t3.setTexture(0, 1.0f, 0.0f);
    t3.setTexture(1, 1.0f, 1.0f);
    t3.setTexture(2, 0.0f, 0.0f);
    t4.setTexture(0, 0.0f, 1.0f);
    t4.setTexture(1, 1.0f, 1.0f);
    t4.setTexture(2, 0.0f, 0.0f);

    t5.setTexture(0, 1.0f, 0.0f);
    t5.setTexture(1, 1.0f, 1.0f);
    t5.setTexture(2, 0.0f, 0.0f);
    t6.setTexture(0, 0.0f, 1.0f);
    t6.setTexture(1, 1.0f, 1.0f);
    t6.setTexture(2, 0.0f, 0.0f);

    t7.setTexture(0, 1.0f, 0.0f);
    t7.setTexture(1, 1.0f, 1.0f);
    t7.setTexture(2, 0.0f, 0.0f);
    t8.setTexture(0, 0.0f, 1.0f);
    t8.setTexture(1, 1.0f, 1.0f);
    t8.setTexture(2, 0.0f, 0.0f);

    t9.setTexture(0, 1.0f, 0.0f);
    t9.setTexture(1, 1.0f, 1.0f);
    t9.setTexture(2, 0.0f, 0.0f);
    t10.setTexture(0, 0.0f, 1.0f);
    t10.setTexture(1, 1.0f, 1.0f);
    t10.setTexture(2, 0.0f, 0.0f);

    t11.setTexture(0, 1.0f, 0.0f);
    t11.setTexture(1, 1.0f, 1.0f);
    t11.setTexture(2, 0.0f, 0.0f);
    t12.setTexture(0, 0.0f, 1.0f);
    t12.setTexture(1, 1.0f, 1.0f);
    t12.setTexture(2, 0.0f, 0.0f);
    
    std::vector<Triangle> list = {t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12};

    while(!this->quit){
        while(SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT){
                this->quit = true;
            }
            if(e.type == SDL_KEYDOWN){
                processInput();
            }
            // if(e.type == SDL_MOUSEMOTION){
            //     int x = e.motion.x;
            //     int y = e.motion.y;
            //     mouse_callback(e, x, y);
            // }
        }

        float currentTime = static_cast<float>(SDL_GetTicks());
        this->deltaTime = currentTime - this->lastTime;
        this->lastTime = currentTime;

        Math::Vector4f background_color(0.0f, 0.0f, 0.0f, 255.0f);
        SDL_SetRenderDrawColor(this->window.GetRenderer(), background_color.x, background_color.y, background_color.z, background_color.w);
        
        clear();
    
        set_model(Transformation::get_model_matrix(model_angle * SDL_GetTicks()));
        set_view(this->camera->GetViewMatrix());
        set_projection(Transformation::get_projection_matrix(45.0f, 1.0f, 0.1f, 50.0f));
        Math::Matrix mvp = projection * view * model;
    
        float f1 = (100 - 0.1) / 2.0;
        float f2 = (100 + 0.1) / 2.0;
    
        for(auto triangle : list){
            Math::Vector4f v[] = {
                mvp * triangle.a().to_Vector4f(1.0f),
                mvp * triangle.b().to_Vector4f(1.0f),
                mvp * triangle.c().to_Vector4f(1.0f)
            };
            for (auto& vec : v) {
                vec = vec / vec.w;
            }
    
            for (auto & vert : v){
                vert.x = std::clamp(vert.x, -1.0f, 1.0f);
                vert.y = std::clamp(vert.y, -1.0f, 1.0f);
    
                vert.x = 0.5 * (this->window.width() - 1) * (vert.x + 1.0);
                vert.y = 0.5 * (this->window.height() - 1) * (vert.y + 1.0);
                vert.z = vert.z * f1 + f2;
            }
    
            for (int i = 0; i < 3; ++i){
                triangle.setVertex(i, v[i].to_Vector3f());
            }

            triangleRasterize(triangle, this->camera->front);
        }
    
        RenderCopy();
    }
}

// set MVP Transformation
void Rasterizer::set_model(const Math::Matrix &m){
    this->model = m;
}
void Rasterizer::set_view(const Math::Matrix &v){
    this->view = v;
}
void Rasterizer::set_projection(const Math::Matrix &p){
    this->projection = p;
}

// Bresen Ham's algorithm
void Rasterizer::drawLine(const Math::Vector3f &begin, const Math::Vector3f &end){
    auto x1 = begin.x, y1 = begin.y;
    auto x2 = end.x, y2 = end.y;

    Color line_color(255.0f, 0.0f, 0.0f, 1.0f);
    SDL_SetRenderDrawColor(this->window.GetRenderer(), line_color.r, line_color.g, line_color.b, line_color.a);

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

        Math::Vector3f point(x, y, 1.0f);
        set_pixel(point, line_color);

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
            point = Math::Vector3f(x, y, 1.0f);
            set_pixel(point, line_color);
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

        Math::Vector3f point(x, y, 1.0f);
        set_pixel(point, line_color);

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
            point = Math::Vector3f(x, y, 1.0f);
            set_pixel(point, line_color);
        }
    }
}
void Rasterizer::drawTriangle(Triangle &t){
    drawLine(t.a(), t.b());
    drawLine(t.b(), t.c());
    drawLine(t.c(), t.a());
}
void Rasterizer::triangleRasterize(const Triangle &t){
    auto v = t.toVector4();

    float min_x = window.width(), max_x = 0;
    float min_y = window.height(), max_y = 0;

    for(int i = 0; i < 3; ++ i){
        min_x = std::min(v[i].x, min_x);
        max_x = std::max(v[i].x, max_x);
        min_y = std::min(v[i].y, min_y);
        max_y = std::max(v[i].y, max_y);
    }

    for(int y = min_y; y < max_y; ++ y){
        for(int x = min_x; x < max_x; ++ x){
            if(insideTriangle(static_cast<float>(x) + 0.5f, static_cast<float>(y) + 0.5f, t.v())){
                auto [alpha, beta, gamma] = computeBarycentric2D(x + 0.5f, y + 0.5f, t.v());
                float w_reciprocal = 1.0f / (alpha / v[0].w + beta / v[1].w + gamma / v[2].w);
                float z_interpolated = alpha * v[0].z / v[0].w + beta * v[1].z / v[1].w + gamma * v[2].z / v[2].w;
                z_interpolated *= w_reciprocal;

                int index = get_index(x, y);
                if(z_interpolated < z_buffer[index]){
                    Color pixel_color = Color::lerp(t.GetColor(0), t.GetColor(1), t.GetColor(2), alpha, beta, gamma);

                    set_pixel(Math::Vector3f(x, y, z_interpolated), pixel_color);
                    z_buffer[index] = z_interpolated;
                }
            }
        }
    }
}
void Rasterizer::triangleRasterize(const Triangle &t, const Math::Vector3f& eye_pos){
    auto v = t.toVector4();

    float min_x = window.width(), max_x = 0;
    float min_y = window.height(), max_y = 0;

    for(int i = 0; i < 3; ++ i){
        min_x = std::min(v[i].x, min_x);
        max_x = std::max(v[i].x, max_x);
        min_y = std::min(v[i].y, min_y);
        max_y = std::max(v[i].y, max_y);
    }

    for(int y = min_y; y < max_y; ++ y){
        for(int x = min_x; x < max_x; ++ x){
            if(insideTriangle(static_cast<float>(x) + 0.5f, static_cast<float>(y) + 0.5f, t.v())){
                auto [alpha, beta, gamma] = computeBarycentric2D(x + 0.5f, y + 0.5f, t.v());
                float w_reciprocal = 1.0f / (alpha / v[0].w + beta / v[1].w + gamma / v[2].w);
                float z_interpolated = alpha * v[0].z / v[0].w + beta * v[1].z / v[1].w + gamma * v[2].z / v[2].w;
                z_interpolated *= w_reciprocal;

                int index = get_index(x, y);
                if(z_interpolated < z_buffer[index]){
                    auto interpolated_color = Math::interpolate(alpha, beta, gamma, t.GetColor(0).GetRGB(), t.GetColor(1).GetRGB(), t.GetColor(2).GetRGB(), 1);
                    auto interpolated_normal = Math::interpolate(alpha, beta, gamma, t.GetNormal(0), t.GetNormal(1), t.GetNormal(2), 1).normalized();
                    auto interpolated_texcoords = Math::interpolate(alpha, beta, gamma, t.GetTexture(0), t.GetTexture(1), t.GetTexture(2), 1);
                    auto interpolated_shadingcoords = Math::interpolate(alpha, beta, gamma, t.a(), t.b(), t.c(), 1);
                    Vertex payload;
                    payload.color = interpolated_color;
                    payload.normal = interpolated_normal.normalized();
                    payload.uv = interpolated_texcoords;
                    payload.v = interpolated_shadingcoords;
                    payload.texture = texture ? std::make_shared<Texture>(*texture) : nullptr;

                    Color pixel_color = fragment_shader(payload, eye_pos);
                    // std::cout << pixel_color.r << " " << pixel_color.g << " " << pixel_color.b << std::endl;

                    set_pixel(Math::Vector3f(x, y, z_interpolated), pixel_color);
                    z_buffer[index] = z_interpolated;
                }
            }
        }
    }
}
void Rasterizer::RenderCopy() {
    void* pixels;
    int pitch;
    SDL_LockTexture(this->window.GetTexture(), nullptr, &pixels, &pitch);

    for (int y = 0; y < this->window.height(); ++y) {
        for (int x = 0; x < this->window.width(); ++x) {
            auto index = get_index(x, y);
            Color color = frame_buf[index] * 255.0f;
            Uint32* pixel = static_cast<Uint32*>(pixels) + y * (pitch / 4) + x;
            *pixel = SDL_MapRGBA(SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888), color.r, color.g, color.b, color.a);
        }
    }
    
    SDL_UnlockTexture(this->window.GetTexture());
    SDL_RenderCopy(this->window.GetRenderer(), this->window.GetTexture(), nullptr, nullptr);
    SDL_RenderPresent(this->window.GetRenderer());
}

std::unique_ptr<uint32_t[]> Rasterizer::frame_buffer() const{
    std::unique_ptr<uint32_t[]> fb = std::make_unique<uint32_t[]>(this->window.height() * this->window.width());
    for(int i = 0; i < frame_buf.size(); ++ i){
        fb.get()[i] = frame_buf[i].toUInt();
    }

    return std::move(fb);
}

void Rasterizer::draw(){
    SDL_SetRelativeMouseMode(SDL_TRUE);
    while(SDL_PollEvent(&e)){
        if(e.type == SDL_QUIT){
            this->quit = true;
        }
        if(e.type == SDL_KEYDOWN){
            processInput();
        }
        if(e.type == SDL_MOUSEMOTION){
            int x = e.motion.x;
            int y = e.motion.y;
            mouse_callback(e, x, y);
        }
        if (e.type == SDL_MOUSEWHEEL) {
            int x = e.wheel.x;
            int y = e.wheel.y;
            scroll_callback(e, x, y);
        }
    }

    float currentTime = static_cast<float>(SDL_GetTicks());
    this->deltaTime = currentTime - this->lastTime;
    this->lastTime = currentTime;
    
    Math::Vector4f background_color(255.0f, 255.0f, 255.0f, 255.0f);
    SDL_SetRenderDrawColor(this->window.GetRenderer(), background_color.x, background_color.y, background_color.z, background_color.w);
    
    clear();

    set_model(Transformation::get_model_matrix(1.0f));
    set_view(this->camera->GetViewMatrix());
    set_projection(Transformation::get_projection_matrix(Math::radians(this->camera->zoom), static_cast<float>(this->window.width()) / this->window.height(), 0.1f, 50.0f));
    Math::Matrix mvp = projection * view * model;

    float f1 = (100 - 0.1) / 2.0;
    float f2 = (100 + 0.1) / 2.0;

    for(auto face : mesh->faces){
        Triangle triangle;
        triangle.setVertex(0, mesh->vertices[face.index[0]].v);
        triangle.setVertex(1, mesh->vertices[face.index[1]].v);
        triangle.setVertex(2, mesh->vertices[face.index[2]].v);

        Math::Vector4f v[] = {
            mvp * triangle.a().to_Vector4f(1.0f),
            mvp * triangle.b().to_Vector4f(1.0f),
            mvp * triangle.c().to_Vector4f(1.0f)
        };
        for (auto& vec : v) {
            vec = vec / vec.w;
        }

        for (auto & vert : v){
            vert.x = std::clamp(vert.x, -1.0f, 1.0f);
            vert.y = std::clamp(vert.y, -1.0f, 1.0f);

            vert.x = 0.5 * this->window.width() * (vert.x + 1.0);
            vert.y = 0.5 * this->window.height() * (vert.y + 1.0);
            vert.z = vert.z * f1 + f2;
        }

        for (int i = 0; i < 3; ++i){
            triangle.setVertex(i, v[i].to_Vector3f());
        }
        triangleRasterize(triangle, this->camera->front);
    }

    RenderCopy();
}

int Rasterizer::get_index(int x, int y) const{
    return (this->window.height() - 1 - y) * this->window.width() + x;
}

int Rasterizer::get_next_ind(){
    return this->next_id ++;
}

void Rasterizer::set_pixel(const Math::Vector3f &p, const Color &color){
    auto index = (this->window.height() - 1 - p.y) * this->window.width() + p.x;
    this->frame_buf[index] = color;
}

void Rasterizer::BindCamera(std::shared_ptr<Camera> _camera){
    this->camera = _camera;
}
void Rasterizer::BindMesh(std::shared_ptr<Mesh> meshes){
    this->mesh = std::move(meshes);
}
void Rasterizer::BindTexture(Texture tex){
    this->texture = tex;
}
void Rasterizer::SetShader(const std::string& shader){
    if(shader == "normal"){
        this->fragment_shader = Shader::normal_fragment_shader;
    }else if(shader == "phong"){
        this->fragment_shader = Shader::phong_fragment_shader;
    }else if(shader == "displace"){
        this->fragment_shader = Shader::displacement_fragment_shader;
    }else if(shader == "texture"){
        this->fragment_shader = Shader::texture_fragment_shader;
    }else if(shader == "bump"){
        this->fragment_shader = Shader::bump_fragment_shader;
    }else{
        std::cerr << "Invalid Shader Input" << std::endl;
    }
}

bool Rasterizer::insideTriangle(float x, float y, const std::vector<Math::Vector3f> v){
    float flag = -1;

    for(int i = 0; i < 3; ++ i){
        Math::Vector3f p0(x, y, 0);
        Math::Vector3f p1 = v[i];
        Math::Vector3f p2 = v[(i + 1) % 3];
        Math::Vector3f v1 = p1 - p0;
        Math::Vector3f v2 = p1 - p2;

        float dz = v1.cross(v2).z;
        if(!dz){
            continue;
        }

        int sign = (dz < 0) ? 0 : 1;

        if(flag == -1){
            flag = sign;
        }
        if(flag != sign){
            return false;
        }
    }

    return true;
}
std::tuple<float, float, float> Rasterizer::computeBarycentric2D(float x, float y, const std::vector<Math::Vector3f> v){
    float c1 = (x * (v[1].y - v[2].y) + (v[2].x - v[1].x) * y + v[1].x * v[2].y - v[2].x * v[1].y) / (v[0].x * (v[1].y - v[2].y) + (v[2].x - v[1].x) * v[0].y + v[1].x * v[2].y - v[2].x * v[1].y);
    float c2 = (x * (v[2].y - v[0].y) + (v[0].x - v[2].x) * y + v[2].x * v[0].y - v[0].x * v[2].y) / (v[1].x * (v[2].y - v[0].y) + (v[0].x - v[2].x) * v[1].y + v[2].x * v[0].y - v[0].x * v[2].y);
    float c3 = (x * (v[0].y - v[1].y) + (v[1].x - v[0].x) * y + v[0].x * v[1].y - v[1].x * v[0].y) / (v[2].x *( v[0].y - v[1].y) + (v[1].x - v[0].x) * v[2].y + v[0].x * v[1].y - v[1].x * v[0].y);
    
    return {c1,c2,c3};
}

void Rasterizer::clear() {
    SDL_RenderClear(this->window.GetRenderer());
    std::fill(z_buffer.begin(), z_buffer.end(), std::numeric_limits<float>::infinity());
    std::fill(frame_buf.begin(), frame_buf.end(), Color::Identity());
}

void Rasterizer::processInput(){
    if(e.key.keysym.sym == SDLK_ESCAPE){
        this->quit = true;
    }

    if(e.key.keysym.sym == SDLK_w || e.key.keysym.sym == SDLK_UP){
        this->camera->ProcessKeyboard(FORWARD, this->deltaTime);
    }
    if(e.key.keysym.sym == SDLK_s || e.key.keysym.sym == SDLK_DOWN){
        this->camera->ProcessKeyboard(BACKWARD, this->deltaTime);
    }
    if(e.key.keysym.sym == SDLK_a || e.key.keysym.sym == SDLK_LEFT){
        this->model_angle += 2.0f * deltaTime;
    }
    if(e.key.keysym.sym == SDLK_d || e.key.keysym.sym == SDLK_RIGHT){
        this->model_angle -= 2.0f * deltaTime;
    }
}

void Rasterizer::mouse_callback(SDL_Event &e, double xposIn, double yposIn){
    float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);

	static float lastX = 1920 / 2.0f;
	static float lastY = 1080 / 2.0f;
	static bool firstMouse = true;

	if (firstMouse) {
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;

	lastX = xpos;
	lastY = ypos;

	camera->ProcessMouseMovement(xoffset, yoffset);
}
void Rasterizer::scroll_callback(SDL_Event &e, double xoffset, double yoffset){
    camera->ProcessMouseScroll(yoffset);
}
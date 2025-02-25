#include <Rasterizer.h>
#include <iostream>
#include <cstdlib>
#include <algorithm>

Rasterizer::Rasterizer(){
    Start();
}
Rasterizer::~Rasterizer(){
    Destroy();
}

void Rasterizer::Start(){
    this->quit = false;
    this->frame_buf.resize(this->window.height() * this->window.width());
    this->z_buffer.resize(this->window.height() * this->window.width());
}
void Rasterizer::Update(){
    this->camera->Update();
    draw();
}
void Rasterizer::Destroy(){  }

// set MVP Transformation
void Rasterizer::set_model(const Matrix &m){
    this->model = m;
}
void Rasterizer::set_view(const Matrix &v){
    this->view = v;
}
void Rasterizer::set_projection(const Matrix &p){
    this->projection = p;
}

// Bresen Ham's algorithm
void Rasterizer::drawLine(const Vector3f &begin, const Vector3f &end){
    auto x1 = begin.x, y1 = begin.y;
    auto x2 = end.x, y2 = end.y;

    Color line_color(255.0f, 0.0f, 0.0f, 1.0f);
    SDL_SetRenderDrawColor(this->window.getRenderer(), line_color.r, line_color.g, line_color.b, line_color.a);

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
            point = Vector3f(x, y, 1.0f);
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

        Vector3f point(x, y, 1.0f);
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
            point = Vector3f(x, y, 1.0f);
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
                    set_pixel(Vector3f(x, y, z_interpolated), Color::lerp(t.getColor(0), t.getColor(1), t.getColor(2), alpha, beta, gamma));
                    z_buffer[index] = z_interpolated;
                }
            }
        }
    }
}
void Rasterizer::render() {
    void* pixels;
    int pitch;
    SDL_LockTexture(this->window.getTexture(), nullptr, &pixels, &pitch);

    for (int y = 0; y < this->window.height(); ++y) {
        for (int x = 0; x < this->window.width(); ++x) {
            auto index = get_index(x, y);
            Color color = frame_buf[index];
            Uint32* pixel = (Uint32*)pixels + y * (pitch / 4) + x;
            *pixel = SDL_MapRGBA(SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888), color.r, color.g, color.b, color.a);
        }
    }

    SDL_UnlockTexture(this->window.getTexture());
    SDL_RenderCopy(this->window.getRenderer(), this->window.getTexture(), nullptr, nullptr);
    SDL_RenderPresent(this->window.getRenderer());
}

std::unique_ptr<uint32_t[]> Rasterizer::frame_buffer() const{
    std::unique_ptr<uint32_t[]> fb = std::make_unique<uint32_t[]>(this->window.height() * this->window.width());
    for(int i = 0; i < frame_buf.size(); ++ i){
        fb.get()[i] = frame_buf[i].toUInt();
    }

    return std::move(fb);
}

void Rasterizer::draw(){
    while(SDL_PollEvent(&e) != 0){
        if(e.type == SDL_QUIT){
            this->quit = true;
        }
        if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE){
            this->quit = true;
        }
    }

    Vector4f background_color(0.0f, 0.0f, 0.0f, 255.0f);
    SDL_SetRenderDrawColor(this->window.getRenderer(), background_color.x, background_color.y, background_color.z, background_color.w);
    
    clear();
    int frame_count = 0;

    set_model(Transformation::get_model_matrix(140.0f));
    set_view(this->camera->getViewMatrix());
    set_projection(Transformation::get_projection_matrix(45.0f, 1.0f, 0.1f, 50.0f));
    Matrix mvp = projection * view * model;

    float f1 = (100 - 0.1) / 2.0;
    float f2 = (100 + 0.1) / 2.0;

    Triangle triangle;
    triangle.setVertex(0, Vector3f(2.0f, 0.0f, -2.0f));
    triangle.setVertex(1, Vector3f(0.0f, 2.0f, -2.0f));
    triangle.setVertex(2, Vector3f(-2.0f, 0.0f, -2.0f));

    Vector4f v[] = {
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

    triangle.setColor(0, 255.0f, 0.0f, 0.0f);
    triangle.setColor(1, 0.0f, 255.0f, 0.0f);
    triangle.setColor(2, 0.0f, 0.0f, 255.0f);

    //drawTriangle(triangle);
    triangleRasterize(triangle);
    render();
    std::cout << "frame count: " << frame_count++ << '\n';
}

int Rasterizer::get_index(int x, int y) const{
    return (this->window.height() - 1 - y) * this->window.width() + x;
}

int Rasterizer::get_next_ind(){
    return this->next_id ++;
}

void Rasterizer::set_pixel(const Vector3f &p, const Color &color){
    auto index = (this->window.height() - 1 - p.y) * this->window.width() + p.x;
    this->frame_buf[index] = color;
}

bool Rasterizer::isQuit() const{
    return this->quit;
}

void Rasterizer::bindCamera(std::shared_ptr<Camera> _camera){
    this->camera = _camera;
}

bool Rasterizer::insideTriangle(float x, float y, const std::vector<Vector3f> v){
    float flag = -1;

    for(int i = 0; i < 3; ++ i){
        Vector3f p0(x, y, 0);
        Vector3f p1 = v[i];
        Vector3f p2 = v[(i + 1) % 3];
        Vector3f v1 = p1 - p0;
        Vector3f v2 = p1 - p2;

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
std::tuple<float, float, float> Rasterizer::computeBarycentric2D(float x, float y, const std::vector<Vector3f> v){
    float c1 = (x * (v[1].y - v[2].y) + (v[2].x - v[1].x) * y + v[1].x * v[2].y - v[2].x * v[1].y) / (v[0].x * (v[1].y - v[2].y) + (v[2].x - v[1].x) * v[0].y + v[1].x * v[2].y - v[2].x * v[1].y);
    float c2 = (x * (v[2].y - v[0].y) + (v[0].x - v[2].x) * y + v[2].x * v[0].y - v[0].x * v[2].y) / (v[1].x * (v[2].y - v[0].y) + (v[0].x - v[2].x) * v[1].y + v[2].x * v[0].y - v[0].x * v[2].y);
    float c3 = (x * (v[0].y - v[1].y) + (v[1].x - v[0].x) * y + v[0].x * v[1].y - v[1].x * v[0].y) / (v[2].x *( v[0].y - v[1].y) + (v[1].x - v[0].x) * v[2].y + v[0].x * v[1].y - v[1].x * v[0].y);
    
    return {c1,c2,c3};
}

void Rasterizer::clear() {
    SDL_RenderClear(this->window.getRenderer());
    std::fill(z_buffer.begin(), z_buffer.end(), std::numeric_limits<float>::infinity());
    std::fill(frame_buf.begin(), frame_buf.end(), Color());
}
#ifndef RASTERIZER_H
#define RASTERIZER_H

#pragma once

#include <IManager.h>

#include <Window.h>
#include <Math.h>
#include <Triangle.h>
#include <Transformation.h>
#include <Camera.h>

#include <tuple>
#include <vector>
#include <map>
#include <memory>

class Rasterizer : public IManager{
public:
    Rasterizer();
    ~Rasterizer();

    void Start() override;
    void Update() override;
    void Destroy() override;

    // set mvp matrix
    void set_model(const Matrix &m);
    void set_view(const Matrix &v);
    void set_projection(const Matrix &p);

    std::unique_ptr<uint32_t[]> frame_buffer() const;

    // for draw loop
    void draw();
    bool isQuit() const;
    void bindCamera(std::shared_ptr<Camera> _camera);

private:
    void drawLine(const Vector3f &begin, const Vector3f &end);
    void drawTriangle(Triangle &t);
    void triangleRasterize(const Triangle &t);
    void render();

    int get_index(int x, int y) const;
    int get_next_ind();

    void set_pixel(const Vector3f &p, const Color &color);
    void clear();

private:
    // MVP Matrixes
    Matrix model;
    Matrix view;
    Matrix projection;

    // buffers
    std::vector<float> z_buffer;
    std::vector<Color> frame_buf;

    // 
    bool insideTriangle(float x, float y, const std::vector<Vector3f> v);
    std::tuple<float, float, float> computeBarycentric2D(float x, float y, const std::vector<Vector3f> v);

    // Main Components
    SDL_Event e;
    std::shared_ptr<Camera> camera;
    Window window;
    bool quit;
    int next_id = 0;
};

#endif
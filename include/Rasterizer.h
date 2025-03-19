#ifndef RASTERIZER_H
#define RASTERIZER_H

#pragma once

#include <IManager.h>

#include <Window.h>
#include <Math.h>
#include <Triangle.h>
#include <Transformation.h>
#include <Camera.h>
#include <Mesh.h>

#include <tuple>
#include <vector>
#include <map>
#include <memory>
#include <functional>

class Rasterizer : public IManager{
public:
    Rasterizer();
    ~Rasterizer();

    static Rasterizer& GetInstance();

    // Show features
    void ShowBresen();
    void ShowRst();

    // set mvp matrix
    void set_model(const Math::Matrix &m);
    void set_view(const Math::Matrix &v);
    void set_projection(const Math::Matrix &p);

    std::unique_ptr<uint32_t[]> frame_buffer() const;

    // for draw loop
    void Execute();
    void BindCamera(std::shared_ptr<Camera> _camera);
    void BindMesh(std::shared_ptr<Mesh> meshes);
    void BindTexture(std::shared_ptr<Texture> tex);

private:
    void Start() override;
    void Update() override;
    void Destroy() override;

    // rst
    void draw();
    void drawLine(const Math::Vector3f &begin, const Math::Vector3f &end);
    void drawTriangle(Triangle &t);
    void triangleRasterize(const Triangle &t, const Math::Vector3f& eye_pos);

    bool insideTriangle(float x, float y, const std::vector<Math::Vector3f> v);
    std::tuple<float, float, float> computeBarycentric2D(float x, float y, const std::vector<Math::Vector3f> v);

    void RenderCopy();

    // index
    int get_index(int x, int y) const;
    int get_next_ind();

    void set_pixel(const Math::Vector3f &p, const Color &color);
    void clear();

    // Event System
    void processInput();
    void mouse_callback(SDL_Event &e, bool &inLoop);
    void scroll_callback(SDL_Event &e);

private:
    // MVP Matrixes
    Math::Matrix model;
    Math::Matrix view;
    Math::Matrix projection;

    // buffers
    std::vector<float> z_buffer;
    std::vector<Color> frame_buf;

    // Main Components
    std::shared_ptr<Camera> camera;
    Window window;
    std::shared_ptr<Mesh> mesh;
    std::function<Color(const Vertex&, const Math::Vector3f&)> fragment_shader;

    bool quit;
    int next_id = 0;
    int frame_count;
    SDL_Event e;
};

#endif
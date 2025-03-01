#ifndef MESH_H
#define MESH_H

#pragma once

#include <SDL2/SDL.h>

#include <Vertex.hpp>
#include <Texture.h>

#include <vector>

class Mesh{
public:
    Mesh();
    Mesh(const std::vector<Vertex>& _vertices, const std::vector<unsigned int>& _indices);
    ~Mesh();

    void LoadMesh(SDL_Renderer* renderer, const std::string& path);

    void MVP(Matrix& mvp);

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;
};

#endif
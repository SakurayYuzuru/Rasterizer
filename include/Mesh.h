#ifndef MESH_H
#define MESH_H

#pragma once

#include <Vertex.hpp>

#include <vector>
#include <string>

struct Mesh{
    Mesh();
    ~Mesh();

    void LoadMesh(const std::string& filepath);
    std::vector<Vertex> vertices;
    std::vector<Face> faces;
};

#endif
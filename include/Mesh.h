#ifndef MESH_H
#define MESH_H

#pragma once

#include <Vertex.hpp>

#include <vector>
#include <string>

class Mesh{
public:
    Mesh();
    ~Mesh();

    bool LoadMesh(const std::string& filepath);

private:
    std::vector<Vertex> vertices;
    std::vector<Face> faces;
};

#endif
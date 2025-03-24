#ifndef VERTEX_HPP
#define VERTEX_HPP

#pragma once

#include <Math.h>
#include <Color.h>
#include <Texture.h>

#include <vector>
#include <memory>

struct Vertex{
    Math::Vector3f v;
    Math::Vector2f uv;
    Color color;
    Math::Vector3f normal;
    std::shared_ptr<Texture> texture;

    Vertex(){
        v = Math::Vector3f::Identity();
        uv = Math::Vector2f::Identity();
        color = Color();
        normal = Math::Vector3f::Identity();
        texture = nullptr;
    }
    Vertex(std::shared_ptr<Texture> tex){
        texture = std::move(tex);
    }

    float x() const{
        return this->v.x;
    }
    float y() const{
        return this->v.y;
    }
    float z() const{
        return this->v.z;
    }
};

struct Face{
    std::vector<int> index;
    std::vector<int> uvIndex;
    std::vector<int> nIndex;
};

#endif
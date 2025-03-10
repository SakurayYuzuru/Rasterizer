#ifndef VERTEX_HPP
#define VERTEX_HPP

#pragma once

#include <Math.h>
#include <Color.hpp>

struct Vertex{
    Math::Vector3f v;
    Math::Vector2f uv;
    Color color;
    Math::Vector3f normal;

    Vertex(){
        v = Math::Vector3f::Identity();
        uv = Math::Vector2f::Identity();
        color = Color();
        normal = Math::Vector3f::Identity();
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
    int index;
    int uvIndex;
    int nIndex;
};

#endif
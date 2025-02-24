#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <Math.h>
#include <Color.hpp>

struct Vertex{
    Vector3f v;
    Vector2f uv;
    Color color;
    Vector3f normal;

    Vertex(){
        v = Vector3f();
        uv = Vector2f();
        color = Color();
        normal = Vector3f();
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

#endif
#ifndef TRIANGLE_H
#define TRIANGLE_H

#pragma once

#include <Vertex.hpp>
#include <array>
#include <vector>

class Triangle{
public:
    Triangle();
    ~Triangle();

    Math::Vector3f a() const;
    Math::Vector3f b() const;
    Math::Vector3f c() const;

    void setVertex(int index, Math::Vector3f vertex);
    void setVertex(int index, Vertex vertex);
    void setColor(int index, float r, float g, float b);
    void setTexture(int index, float s, float t);
    void setNormal(int index, Math::Vector3f n);

    std::vector<Math::Vector3f> v() const;
    Color GetColor(int index) const;
    Math::Vector2f GetTexture(int index) const;
    Math::Vector3f GetNormal(int index) const;

    std::array<Math::Vector4f, 3> toVector4() const;

private:
    Vertex vertexes[3];
};

#endif
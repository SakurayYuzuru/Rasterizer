#ifndef TRIANGLE_H
#define TRIANGLE_H

#pragma once

#include <Vertex.hpp>
#include <array>
#include <vector>

class Triangle{
public:
    Triangle();
    ~Triangle() = default;

    Math::Vector3f a();
    Math::Vector3f b();
    Math::Vector3f c();

    void setVertex(int index, Math::Vector3f vertex);
    void setColor(int index, float r, float g, float b);
    void setTexture(int index, float s, float t);
    void setNormal(int index, Math::Vector3f n);

    std::vector<Math::Vector3f> v() const;
    Color getColor(int index) const;
    Math::Vector2f getTexture() const;
    Math::Vector3f getNormal() const;

    std::array<Math::Vector4f, 3> toVector4() const;

    Triangle operator*(Math::Matrix &m);

private:
    Vertex vertexes[3];
};

#endif
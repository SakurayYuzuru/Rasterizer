#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <Vertex.hpp>
#include <array>
#include <vector>

class Triangle{
public:
    Triangle();
    ~Triangle() = default;

    Vector3f a();
    Vector3f b();
    Vector3f c();

    void setVertex(int index, Vector3f vertex);
    void setColor(int index, float r, float g, float b);
    void setTexture(int index, float s, float t);
    void setNormal(int index, Vector3f n);

    std::vector<Vector3f> v() const;
    Color getColor(int index) const;
    Vector2f getTexture() const;
    Vector3f getNormal() const;

    std::array<Vector4f, 3> toVector4() const;

private:
    Vertex vertexes[3];
};

#endif
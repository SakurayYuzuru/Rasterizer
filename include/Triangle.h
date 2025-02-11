#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <Math.h>
#include <array>

class Triangle{
public:
    Vector3f v[3];
    Vector3f colors[3];
    Vector2f uv_coords[3];
    Vector3f normals[3];

    Triangle();

    Vector3f a() const;
    Vector3f b() const;
    Vector3f c() const;

    void setVertex(int index, Vector3f vertex);
    void setColor(int index, float r, float g, float b);
    void setTexture(int index, float s, float t);
    void setNormal(int index, Vector3f n);

    std::array<Vector4f, 3> toVector4() const;
};

#endif
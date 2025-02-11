#include <Triangle.h>
#include <stdexcept>
#include <algorithm>

Triangle::Triangle(){
    v[0] = Vector3f();
    v[1] = Vector3f();
    v[2] = Vector3f();

    colors[0] = Vector3f();
    colors[1] = Vector3f();
    colors[2] = Vector3f();

    uv_coords[0] = Vector2f();
    uv_coords[1] = Vector2f();
    uv_coords[2] = Vector2f();

    normals[0] = Vector3f();
    normals[1] = Vector3f();
    normals[2] = Vector3f();
}

void Triangle::setVertex(int index, Vector3f vertex){
    v[index] = vertex;
}

void Triangle::setColor(int index, float r, float g, float b){
    if((r < 0.0f) || (r > 255.0f) || (g < 0.0f) || (g > 255.0f) || (b < 0.0f) || (b > 255.0f)){
        throw std::runtime_error("Invalid color value");
    }

    colors[index] = Vector3f(r / 255.0f, g / 255.0f, b / 255.0f);
}

void Triangle::setTexture(int index, float s, float t){
    uv_coords[index] = Vector2f(s, t);
}

void Triangle::setNormal(int index, Vector3f n){
    normals[index] = n;
}

std::array<Vector4f, 3> Triangle::toVector4() const{
    std::array<Vector4f, 3> res;
    std::transform(std::begin(v), std::end(v), res.begin(), [](auto &vec){
        return Vector4f(vec.x, vec.y, vec.z, 1.0f);
    });

    return res;
}
#include <Triangle.h>
#include <stdexcept>
#include <algorithm>

Triangle::Triangle(){
    vertexes[0] = Vertex();
    vertexes[1] = Vertex();
    vertexes[2] = Vertex();
}

Vector3f Triangle::a(){
    return this->vertexes[0].v;
}
Vector3f Triangle::b(){
    return this->vertexes[1].v;
}
Vector3f Triangle::c(){
    return this->vertexes[2].v;
}

void Triangle::setVertex(int index, Vector3f vertex){
    vertexes[index].v = vertex;
}
void Triangle::setColor(int index, float r, float g, float b){
    vertexes[index].color = Color(r, g, b);
}
void Triangle::setTexture(int index, float s, float t){
    vertexes[index].uv = Vector2f(s, t);
}
void Triangle::setNormal(int index, Vector3f n){
    vertexes[index].normal = n;
}

std::vector<Vector3f> Triangle::v() const{
    std::vector<Vector3f> vex = {vertexes[0].v, vertexes[1].v, vertexes[2].v};

    return vex;
}
Color Triangle::getColor(int index) const{
    return this->vertexes[index].color;
}

std::array<Vector4f, 3> Triangle::toVector4() const{
    std::array<Vector4f, 3> res;
    std::transform(std::begin(vertexes), std::end(vertexes), res.begin(), [](auto &vec){
        return Vector4f(vec.x(), vec.y(), vec.z(), 1.0f);
    });

    return res;
}
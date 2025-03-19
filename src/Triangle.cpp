#include <Triangle.h>
#include <stdexcept>
#include <algorithm>

Triangle::Triangle(){
    vertexes[0] = Vertex();
    vertexes[1] = Vertex();
    vertexes[2] = Vertex();
}
Triangle::~Triangle() { }

Math::Vector3f Triangle::a() const{
    return this->vertexes[0].v;
}
Math::Vector3f Triangle::b() const{
    return this->vertexes[1].v;
}
Math::Vector3f Triangle::c() const{
    return this->vertexes[2].v;
}

void Triangle::setVertex(int index, Math::Vector3f vertex){
    vertexes[index].v = vertex;
}
void Triangle::setVertex(int index, Vertex vertex){
    setVertex(index, vertex.v);
    setColor(index, vertex.color.r, vertex.color.g, vertex.color.b);
    setTexture(index, vertex.uv.x, vertex.uv.y);
    setNormal(index, vertex.normal);
}
void Triangle::setColor(int index, float r, float g, float b){
    vertexes[index].color = Color(r, g, b);
}
void Triangle::setTexture(int index, float s, float t){
    vertexes[index].uv = Math::Vector2f(s, t);
}
void Triangle::setNormal(int index, Math::Vector3f n){
    vertexes[index].normal = n;
}

std::vector<Math::Vector3f> Triangle::v() const{
    std::vector<Math::Vector3f> vex = {vertexes[0].v, vertexes[1].v, vertexes[2].v};

    return vex;
}
Color Triangle::GetColor(int index) const{
    return this->vertexes[index].color;
}
Math::Vector2f Triangle::GetTexture(int index) const{
    return this->vertexes[index].uv;
}
Math::Vector3f Triangle::GetNormal(int index) const{
    return this->vertexes[index].normal;
}

std::array<Math::Vector4f, 3> Triangle::toVector4() const{
    std::array<Math::Vector4f, 3> res;
    std::transform(std::begin(vertexes), std::end(vertexes), res.begin(), [](auto &vec){
        return Math::Vector4f(vec.x(), vec.y(), vec.z(), 1.0f);
    });

    return res;
}
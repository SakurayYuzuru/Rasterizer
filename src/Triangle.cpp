#include <Triangle.h>
#include <stdexcept>
#include <algorithm>

Triangle::Triangle(){
    vertexes[0] = Vertex();
    vertexes[1] = Vertex();
    vertexes[2] = Vertex();
}

Math::Vector3f Triangle::a(){
    return this->vertexes[0].v;
}
Math::Vector3f Triangle::b(){
    return this->vertexes[1].v;
}
Math::Vector3f Triangle::c(){
    return this->vertexes[2].v;
}

void Triangle::setVertex(int index, Math::Vector3f vertex){
    vertexes[index].v = vertex;
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
Color Triangle::getColor(int index) const{
    return this->vertexes[index].color;
}

std::array<Math::Vector4f, 3> Triangle::toVector4() const{
    std::array<Math::Vector4f, 3> res;
    std::transform(std::begin(vertexes), std::end(vertexes), res.begin(), [](auto &vec){
        return Math::Vector4f(vec.x(), vec.y(), vec.z(), 1.0f);
    });

    return res;
}

Triangle Triangle::operator*(Math::Matrix &m){
    for(int i = 0; i < 3; ++ i){
        this->vertexes[i].v = this->vertexes[i].v * m;
    }

    return *this;
}
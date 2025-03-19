#include <Color.h>

Color::Color(float _r, float _g, float _b){
    if((_r < 0.0f) || (_r > 255.0f) || 
        (_g < 0.0f) || (_g > 255.0f) || 
        (_b < 0.0f) || (_b > 255.0f)){
        std::cerr << "Invalid Color Value: " << _r << " " << _g << " " << _b << std::endl;
    }

    this->r = _r;
    this->g = _g;
    this->b = _b;
    this->a = 1.0f;
}
Color::Color(Math::Vector3f color){
    if((color.x < 0.0f) || (color.x > 255.0f) || 
        (color.y < 0.0f) || (color.y > 255.0f) || 
        (color.z < 0.0f) || (color.z > 255.0f)){
        std::cerr << "Invalid Color Value: " << color.x << " " << color.y << " " << color.z << std::endl;
    }

    this->r = color.x;
    this->g = color.y;
    this->b = color.z;
    this->a = 1.0f;
}
Color::Color(float _r, float _g, float _b, float _a){
    if((_r < 0.0f) || (_r > 255.0f) || 
        (_g < 0.0f) || (_g > 255.0f) || 
        (_b < 0.0f) || (_b > 255.0f) ||
        (_a < 0.0f) || (_a > 1.0f)){
        std::cerr << "Invalid Color Value: " << _r << " " << _g << " " << _b << std::endl;
    }

    this->r = _r;
    this->g = _g;
    this->b = _b;
    this->a = _a;
}

Color Color::operator*(const float& k) const{
    return Color(this->GetRGB() * k);
}
Color Color::operator/(const float& k) const{
    return Color(this->GetRGB() / k);
}
Math::Vector3f Color::GetRGB() const{
    return Math::Vector3f(this->r, this->g, this->b);
}

Color Color::Identity(){
    return Color();
}

uint32_t Color::toUInt() const{
    uint8_t r = static_cast<uint8_t>(this->r * 255.0f);
    uint8_t g = static_cast<uint8_t>(this->g * 255.0f);
    uint8_t b = static_cast<uint8_t>(this->b * 255.0f);
    uint8_t a = static_cast<uint8_t>(this->a * 255.0f);

    return (static_cast<uint32_t>(a) << 24) | (static_cast<uint32_t>(r) << 16) |
        (static_cast<uint32_t>(g) << 8) | static_cast<uint32_t>(b);
}

Color Color::lerp(const Color& A, const Color& B, const Color& C, float u, float v, float w) {
    float r = u * A.r + v * B.r + w * C.r;
    float g = u * A.g + v * B.g + w * C.g;
    float b = u * A.b + v * B.b + w * C.b;

    r = std::min(std::max(r, 0.0f), 255.0f);
    g = std::min(std::max(g, 0.0f), 255.0f);
    b = std::min(std::max(b, 0.0f), 255.0f);

    return Color(r, g, b); 
}
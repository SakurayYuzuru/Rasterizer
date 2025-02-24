#ifndef COLOR_HPP
#define COLOR_HPP

#include <cstdint>

struct Color{
    float r, g, b, a;

    Color() : r(0.0f), g(0.0f), b(0.0f), a(1.0f) {}
    Color(float _r, float _g, float _b){
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
    Color(float _r, float _g, float _b, float _a){
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

    uint32_t toUInt() const{
        uint8_t r = static_cast<uint8_t>(this->r * 255.0f);
        uint8_t g = static_cast<uint8_t>(this->g * 255.0f);
        uint8_t b = static_cast<uint8_t>(this->b * 255.0f);
        uint8_t a = static_cast<uint8_t>(this->a * 255.0f);

        return (static_cast<uint32_t>(a) << 24) | (static_cast<uint32_t>(r) << 16) |
            (static_cast<uint32_t>(g) << 8) | static_cast<uint32_t>(b);
    }

    static Color lerp(const Color& A, const Color& B, const Color& C, float u, float v, float w) {
        float r = u * A.r + v * B.r + w * C.r;
        float g = u * A.g + v * B.g + w * C.g;
        float b = u * A.b + v * B.b + w * C.b;

        r = std::min(std::max(r, 0.0f), 255.0f);
        g = std::min(std::max(g, 0.0f), 255.0f);
        b = std::min(std::max(b, 0.0f), 255.0f);

        return Color(r, g, b); 
    }
};

#endif
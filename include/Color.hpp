#ifndef COLOR_HPP
#define COLOR_HPP

#include <stdexcept>

struct Color{
    float r, g, b, a;

    Color() : r(0.0f), g(0.0f), b(0.0f), a(1.0f) {}
    Color(float _r, float _g, float _b){
        if((_r < 0.0f) || (_r > 255.0f) || 
            (_g < 0.0f) || (_g > 255.0f) || 
            (_b < 0.0f) || (_b > 255.0f)){
            throw std::runtime_error("Invalid color value");
        }

        this->r = _r / 255.0f;
        this->g = _g / 255.0f;
        this->b = _b / 255.0f;
        this->a = 1.0f;
    }
    Color(float _r, float _g, float _b, float _a){
        if((_r < 0.0f) || (_r > 255.0f) || 
            (_g < 0.0f) || (_g > 255.0f) || 
            (_b < 0.0f) || (_b > 255.0f) ||
            (_a < 0.0f) || (_a > 1.0f)){
            throw std::runtime_error("Invalid color value");
        }

        this->r = _r / 255.0f;
        this->g = _g / 255.0f;
        this->b = _b / 255.0f;
        this->a = _a;
    }
};

#endif
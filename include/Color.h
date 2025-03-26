#ifndef COLOR_H
#define COLOR_H

#pragma once

#include <Math.h>

#include <cstdint>

struct Color{
    float r, g, b, a;

    Color() {}
    Color(float _r, float _g, float _b);
    Color(Math::Vector3f color);
    Color(float _r, float _g, float _b, float _a);

    Color operator*(const float& k) const;
    Color operator/(const float& k) const;
    std::vector<float> format() const;
    Math::Vector3f GetRGB() const;

    static Color Identity();

    uint32_t toUInt() const;

    static Color lerp(const Color& A, const Color& B, const Color& C, float u, float v, float w);
};

#endif
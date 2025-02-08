#ifndef RASTERIZER_H
#define RASTERIZER_H

#pragma once

#include <Window.h>

#include <Math.h>

class Rasterizer{
public:
    Rasterizer();
    Rasterizer(Window _window);
    ~Rasterizer();

    void draw();

private:
    void drawLine(Vector3f &begin, Vector3f &end);
    void drawTriangle(Vector3f &a, Vector3f &b, Vector3f &c);

    Window window;
};

#endif
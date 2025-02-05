#ifndef RASTERIZER_H
#define RASTERIZER_H

#pragma once

#include <IManager.h>
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

    Window window;
};

#endif
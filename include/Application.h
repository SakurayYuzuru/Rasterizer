#ifndef APPLICATION_H
#define APPLICATION_H

#pragma once

#include <IManager.h>

#include <ArgumentParser.h>
#include <CommandManager.h>
#include <Rasterizer.h>
#include <Camera.h>
#include <Mesh.h>
#include <Texture.h>

#include <memory>

class Application : private IManager{
public:
    Application();
    ~Application();
    void Execute();
    int exit();

private:
    void Start() override;
    void Update() override;
    void Destroy() override;

private:
    ArgumentParser arg;
    CommandManager cmd;
    std::shared_ptr<Rasterizer> rst;
    std::shared_ptr<Camera> camera;
    std::shared_ptr<Mesh> mesh;
    Texture texture;
};

#endif
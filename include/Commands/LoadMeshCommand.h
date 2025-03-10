#ifndef LOAD_MESH_COMMAND_H
#define LOAD_MESH_COMMAND_H

#pragma once

#include <ICommand.h>

#include <Mesh.h>

#include <string>

class LoadMeshCommand : public ICommand{
public:
    LoadMeshCommand(const Mesh& mesh);
    ~LoadMeshCommand();

    void Execute(const std::string& arg) override;
    bool Successful() override;

private:
    Mesh mesh;
    std::string path;
    bool flag;
};

#endif
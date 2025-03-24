#ifndef LOAD_MESH_COMMAND_H
#define LOAD_MESH_COMMAND_H

#pragma once

#include <ICommand.h>

#include <Mesh.h>

#include <string>
#include <memory>

class LoadMeshCommand : public ICommand{
public:
    LoadMeshCommand();
    ~LoadMeshCommand();

    void Execute(const std::string& arg) override;
};

#endif
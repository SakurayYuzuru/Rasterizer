#include <LoadMeshCommand.h>

LoadMeshCommand::LoadMeshCommand(std::shared_ptr<Mesh> mesh) : mesh(mesh) { }
LoadMeshCommand::~LoadMeshCommand() { }

void LoadMeshCommand::Execute(const std::string& arg){
    this->mesh->LoadMesh(arg);
}
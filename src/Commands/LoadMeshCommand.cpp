#include <LoadMeshCommand.h>

LoadMeshCommand::LoadMeshCommand(const Mesh& mesh){
    this->mesh = mesh;
    this->flag = false;
}
LoadMeshCommand::~LoadMeshCommand() { }

void LoadMeshCommand::Execute(const std::string& arg){
    this->flag = this->mesh.LoadMesh(arg);
}

bool LoadMeshCommand::Successful(){
    return this->flag;
}
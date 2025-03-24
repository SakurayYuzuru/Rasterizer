#include <LoadMeshCommand.h>
#include <iostream>

LoadMeshCommand::LoadMeshCommand() { }
LoadMeshCommand::~LoadMeshCommand() { }

void LoadMeshCommand::Execute(const std::string& arg){
    std::cout << "Loading Model..." << std::endl;
}
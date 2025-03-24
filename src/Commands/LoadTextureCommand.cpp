#include <LoadTextureCommand.h>
#include <iostream>

LoadTextureCommand::LoadTextureCommand() { }
LoadTextureCommand::~LoadTextureCommand() { }

void LoadTextureCommand::Execute(const std::string& arg){
    std::cout << "Loading Texture..." << std::endl;
}
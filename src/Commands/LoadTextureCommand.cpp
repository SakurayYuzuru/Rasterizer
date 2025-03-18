#include <LoadTextureCommand.h>

LoadTextureCommand::LoadTextureCommand(std::shared_ptr<Texture> tex) : texture(tex) { }
LoadTextureCommand::~LoadTextureCommand() { }

void LoadTextureCommand::Execute(const std::string& arg){
    this->texture->LoadTexture(arg);
}
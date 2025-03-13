#include <LoadTextureCommand.h>

LoadTextureCommand::LoadTextureCommand(std::shared_ptr<Texture> tex) : texture(tex) { }

void LoadTextureCommand::Execute(const std::string& arg){
    this->texture->LoadTexture(arg);
}
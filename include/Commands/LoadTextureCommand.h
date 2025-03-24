#ifndef LOAD_TEXTURE_COMMAND_H
#define LOAD_TEXTURE_COMMAND_H

#pragma once

#include <ICommand.h>
#include <Texture.h>

#include <memory>

class LoadTextureCommand : public ICommand{
public:
    LoadTextureCommand();
    ~LoadTextureCommand();

    void Execute(const std::string& arg) override;
};

#endif
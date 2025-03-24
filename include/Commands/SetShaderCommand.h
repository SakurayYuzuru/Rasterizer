#ifndef SET_SHADER_COMMAND_H
#define SET_SHADER_COMMAND_H

#pragma once

#include <ICommand.h>

class SetShaderCommand : public ICommand{
public:
    void Execute(const std::string& arg) override;
};

#endif
#ifndef SHOW_Z_BUFFER_COMMAND_H
#define SHOW_Z_BUFFER_COMMAND_H

#pragma once

#include <ICommand.h>

class ShowZBufferCommand : public ICommand{
public:
    void Execute(const std::string& arg) override;
};

#endif
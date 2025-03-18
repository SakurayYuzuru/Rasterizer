#ifndef EXECUTE_COMMAND_H
#define EXECUTE_COMMAND_H

#pragma once

#include <ICommand.h>

class ExecuteCommand : public ICommand{
public:
    void Execute(const std::string& arg) override;
};

#endif
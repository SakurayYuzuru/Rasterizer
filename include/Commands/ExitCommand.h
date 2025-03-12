#ifndef EXIT_COMMAND_H
#define EXIT_COMMAND_H

#pragma once

#include <ICommand.h>

class ExitCommand : public ICommand{
public:
    ExitCommand();
    ~ExitCommand();
    void Execute(const std::string& arg) override;
};

#endif
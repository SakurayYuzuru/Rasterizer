#ifndef HELP_COMMAND_H
#define HELP_COMMAND_H

#pragma once

#include <ICommand.h>

class HelpCommand : public ICommand{
public:
    HelpCommand();
    ~HelpCommand();

    void Execute(const std::string& arg) override;
    bool Successful() override;
};

#endif
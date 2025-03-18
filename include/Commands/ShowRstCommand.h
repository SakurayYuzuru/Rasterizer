#ifndef SHOW_RST_COMMAND_H
#define SHOW_RST_COMMAND_H

#pragma once

#include <ICommand.h>

class ShowRstCommand : public ICommand{
public:
    ShowRstCommand();
    ~ShowRstCommand();

    void Execute(const std::string& arg) override;
};

#endif
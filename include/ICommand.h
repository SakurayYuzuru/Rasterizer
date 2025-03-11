#ifndef ICOMMAND_H
#define ICOMMAND_H

#pragma once

#include <string>

class ICommand{
public:
    virtual ~ICommand() = default;
    virtual void Execute(const std::string& arg) = 0;
};

#endif
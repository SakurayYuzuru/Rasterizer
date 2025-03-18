#ifndef SHOW_BRESEN_HAM_COMMAND_H
#define SHOW_BRESEN_HAM_COMMAND_H

#pragma once

#include <ICommand.h>

#include <Rasterizer.h>

#include <memory>
#include <string>

class ShowBresenHamCommand : public ICommand{
public:
    explicit ShowBresenHamCommand();
    ~ShowBresenHamCommand();

    void Execute(const std::string& arg) override;
};

#endif
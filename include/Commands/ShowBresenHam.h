#ifndef SHOW_BRESEN_HAM_H
#define SHOW_BRESEN_HAM_H

#pragma once

#include <ICommand.h>

#include <Rasterizer.h>

#include <memory>
#include <string>

class ShowBresenHam : public ICommand{
public:
    explicit ShowBresenHam();
    ~ShowBresenHam();

    void Execute(const std::string& arg) override;
};

#endif
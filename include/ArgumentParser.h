#ifndef ARGUMENTS_PARSER_H
#define ARGUMENTS_PARSER_H

#pragma once

#include <ICommand.h>
#include <IManager.h>

#include <HelpCommand.h>

#include <unordered_map>
#include <string>
#include <memory>

class ArgumentParser : public IManager{
public:
    ArgumentParser();
    ~ArgumentParser();
    bool Execute();

    void AddOption(const std::string& name, std::unique_ptr<ICommand> cmd);

private:
    void Start() override;
    void Update() override;
    void Destroy() override;

    bool processInput();

private:
    std::unordered_map<std::string, std::unique_ptr<ICommand>> options;
};

#endif
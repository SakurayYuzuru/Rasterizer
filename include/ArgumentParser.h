#ifndef ARGUMENTS_PARSER_H
#define ARGUMENTS_PARSER_H

#pragma once

#include <ICommand.h>
#include <IManager.h>

#include <HelpCommand.h>
#include <CommandManager.h>

#include <string>
#include <tuple>

class ArgumentParser : public IManager{
public:
    explicit ArgumentParser(CommandManager& _cmdManager);
    ~ArgumentParser();
    std::tuple<int, std::string, std::string> Execute();

private:
    void Start() override;
    void Update() override;
    void Destroy() override;

    std::tuple<int, std::string, std::string> processInput();

private:
    CommandManager& cmdManager;
};

#endif
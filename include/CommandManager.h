#ifndef COMMAND_MANAGER_H
#define COMMAND_MANAGER_H

#pragma once

#include <ICommand.h>

#include <Event.h>

#include <string>
#include <unordered_map>
#include <memory>

class CommandManager{
public:
    CommandManager();
    ~CommandManager();

    void RegisterCommand(const std::string& name, std::unique_ptr<ICommand> cmd);
    void RegisterEvent(const std::string& name, std::function<void()> callback);
    void Execute(const std::string& name, const std::string& args);
    size_t find(const std::string& name);

private:
    std::unordered_map<std::string, std::unique_ptr<ICommand>> commands;
    std::unordered_map<std::string, Event> events;
};

#endif
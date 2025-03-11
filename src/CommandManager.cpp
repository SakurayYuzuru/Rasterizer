#include <CommandManager.h>
#include <iostream>

#include <HelpCommand.h>
#include <ShowBresenHam.h>

CommandManager::CommandManager() {
    commands["--help"] = std::make_unique<HelpCommand>();
    commands["--bresen_ham"] = std::make_unique<ShowBresenHam>();
}
CommandManager::~CommandManager() { }

void CommandManager::RegisterCommand(const std::string& name, std::unique_ptr<ICommand> cmd){
    if(cmd){
        this->commands[name] = std::move(cmd);
    }
}

void CommandManager::Execute(const std::string& name, const std::string& args){{
    if(find(name)){
        this->commands[name]->Execute(args);
    }else{
        std::cout << "\aInvalid Option!" << std::endl;
        this->commands["--help"]->Execute("");
    }
}}

size_t CommandManager::find(const std::string& name){
    return commands.count(name);
}
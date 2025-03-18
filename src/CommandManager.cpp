#include <CommandManager.h>
#include <iostream>

#include <ExitCommand.h>
#include <HelpCommand.h>
#include <ShowBresenHamCommand.h>
#include <ShowRstCommand.h>
#include <ExecuteCommand.h>

CommandManager::CommandManager() {
    commands["exit"] = std::make_unique<ExitCommand>();
    commands["help"] = std::make_unique<HelpCommand>();
    commands["bresen_ham"] = std::make_unique<ShowBresenHamCommand>();
    commands["rst"] = std::make_unique<ShowRstCommand>();
    commands["run"] = std::make_unique<ExecuteCommand>();
}
CommandManager::~CommandManager() { }

void CommandManager::RegisterCommand(const std::string& name, std::unique_ptr<ICommand> cmd){
    if(cmd){
        this->commands[name] = std::move(cmd);
    }
}
void CommandManager::RegisterEvent(const std::string& name, std::function<void()> callback){
    this->events[name].Subscribe(callback);
}

void CommandManager::Execute(const std::string& name, const std::string& args){{
    if(find(name)){
        this->commands[name]->Execute(args);
        if(events.find(name) != events.end()){
            std::cout << "Invoked" << std::endl;
            events[name].Invoke();
        }
    }else{
        std::cout << "\aInvalid Option!" << std::endl;
        this->commands["help"]->Execute("");
    }
}}

size_t CommandManager::find(const std::string& name){
    return commands.count(name);
}
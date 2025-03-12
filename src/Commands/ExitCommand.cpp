#include <ExitCommand.h>
#include <iostream>

ExitCommand::ExitCommand(){ }
ExitCommand::~ExitCommand(){ }

void ExitCommand::Execute(const std::string& arg){
    std::cout << "Exit" << std::endl;
}
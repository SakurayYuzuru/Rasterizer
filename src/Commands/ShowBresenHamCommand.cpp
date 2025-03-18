#include <ShowBresenHamCommand.h>
#include <iostream>

ShowBresenHamCommand::ShowBresenHamCommand(){ }
ShowBresenHamCommand::~ShowBresenHamCommand(){ }

void ShowBresenHamCommand::Execute(const std::string& arg){
    std::cout << "Show Bresen Ham's Algorithm." << std::endl;
}
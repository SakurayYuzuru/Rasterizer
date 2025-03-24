#include <SetShaderCommand.h>
#include <iostream>

void SetShaderCommand::Execute(const std::string& arg){
    std::cout << "Set " << arg << "Successful!" << std::endl; 
}
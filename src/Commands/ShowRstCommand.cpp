#include <ShowRstCommand.h>
#include <iostream>

ShowRstCommand::ShowRstCommand() { }
ShowRstCommand::~ShowRstCommand() { }

void ShowRstCommand::Execute(const std::string& arg){
    std::cout << "Show Rasterization and Color Blending Algorithms" << std::endl;
}
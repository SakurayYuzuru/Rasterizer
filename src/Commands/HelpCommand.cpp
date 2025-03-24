#include <HelpCommand.h>
#include <iostream>

HelpCommand::HelpCommand() { }
HelpCommand::~HelpCommand() { }

void HelpCommand::Execute(const std::string& arg){
    std::cout << "Usage: [Options] [args]" << std::endl
                  << "Commands:" << std::endl
                  << "  exit                      Quit" << std::endl
                  << "  help                      Show this help message" << std::endl
                  << "  bresen_ham                Show the Bresen Ham's Algorithm" << std::endl
                  << "  rst                       Show the rasterization with a triangle" << std::endl
                  << "  shader                    Set the shader for this rasterization" << std::endl
                  << "  model <model-path>        Set model" << std::endl
                  << "  texture <picture-path>    Set texture" << std::endl
                  << "  run                       Execute for rendering" << std::endl;
}
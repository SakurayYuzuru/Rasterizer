#include <ArgumentParser.h>
#include <iostream>
#include <fstream>
#include <sstream>

ArgumentParser::ArgumentParser(CommandManager& _cmdManager) : cmdManager(_cmdManager) {
    Start();
}
ArgumentParser::~ArgumentParser(){
    Destroy();
}
std::tuple<int, std::string, std::string> ArgumentParser::Execute(){
    Update();

    return processInput();
}

void ArgumentParser::Start(){ }
void ArgumentParser::Update(){ }
void ArgumentParser::Destroy(){ }

std::tuple<int, std::string, std::string> ArgumentParser::processInput(){
    std::string input;
    while(true){
        std::cout << "(SRasterizer) $ ";
        std::getline(std::cin, input);
        std::istringstream iss(input);
        std::string command;
        std::string arg;


        if(!(iss >> command)){
            continue;
        }
        if(!(iss >> arg)){
            arg = "";
        }

        if(command == "exit" || command == "quit"){
            std::cout << "Quit" << std::endl;
            return {-1, command, arg};
        }else if(command == "--help"){
            return {0, command, arg};
        }else if(command == "--bresem_ham"){
            return {2, command, arg};
        }else if(command == "--rst"){
            return {3, command, arg};
        }else if(command == "--model"){
            if(arg.empty()){
                return {0, "--help", arg};
            }else{
                this->cmdManager.Execute(command, arg);
                if(this->cmdManager.find(command)){
                    std::cout << "[Mesh] Link Successful!" << std::endl;
                    return {1, command, arg};
                }else{
                    continue;
                }
            }
        }
    }
}
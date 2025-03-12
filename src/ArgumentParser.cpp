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

        std::cout << command << " " << arg << std::endl;

        if(command == "--exit"){
            return std::make_tuple(-1, command, arg);
        }else if(command == "--help"){
            return std::make_tuple(0, command, arg);
        }else if(command == "--model"){
            if(arg.empty()){
                return std::make_tuple(0, "--help", arg);
            }else{
                this->cmdManager.Execute(command, arg);
                if(this->cmdManager.find(command) && arg.rfind(".obj")){
                    std::cout << "[Mesh] Link Successful!" << std::endl;
                    return std::make_tuple(1, command, arg);
                }else{
                    continue;
                }
            }
        }else if(command == "--bresem_ham"){
            return std::make_tuple(2, command, arg);
        }else if(command == "--rst"){
            return std::make_tuple(3, command, arg);
        }else{
            return std::make_tuple(0, "--help", arg);
        }
    }
}
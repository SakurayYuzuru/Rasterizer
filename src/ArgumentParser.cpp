#include <ArgumentParser.h>
#include <iostream>
#include <fstream>
#include <sstream>

ArgumentParser::ArgumentParser(){
    Start();
}
ArgumentParser::~ArgumentParser(){
    Destroy();
}
bool ArgumentParser::Execute(){
    Update();

    return processInput();
}

void ArgumentParser::Start(){
    options["--help"] = std::make_unique<HelpCommand>();
}
void ArgumentParser::Update(){ }
void ArgumentParser::Destroy(){ }

bool ArgumentParser::processInput(){
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

        if(command == "exit" || command == "quit"){
            std::cout << "Quit" << std::endl;
            return false;
        }else if(command == "--help"){
            options["--help"]->Execute("");
        }else if(command == "--model"){
            if(!(iss >> arg)){
                options["--help"]->Execute("");
            }else{
                options["--model"]->Execute(arg);
                if(options["--model"]->Successful()){
                    std::cout << "[Mesh] Link Successful!" << std::endl;
                    return true;
                }else{
                    continue;
                }
            }
        }
    }
}

void ArgumentParser::AddOption(const std::string& name, std::unique_ptr<ICommand> cmd){
    options[name] = std::move(cmd);
}
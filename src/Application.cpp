#include <Application.h>
#include <Mesh.h>

#include <LoadMeshCommand.h>
#include <ShowBresenHam.h>

Application::Application() : cmd(), arg(cmd){
    Start();
}
Application::~Application(){
    Destroy();
}
void Application::Execute(){
    Update();
}

void Application::Start(){
    std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
    cmd.RegisterCommand("--model", std::make_unique<LoadMeshCommand>(mesh));
    this->camera = std::make_shared<Camera>();
}
void Application::Update(){
    std::shared_ptr<Rasterizer> rst = std::make_shared<Rasterizer>();
    rst->BindCamera(camera);
    rst->ShowRst();

    // int flag = 1;
    // while(flag){
    //     auto command = arg.Execute();

    //     if(std::get<0>(command) == -1){
    //         flag = exit();
    //     }else if(std::get<0>(command) == 2){
    //         std::shared_ptr<Rasterizer> rst = std::make_shared<Rasterizer>();
    //         cmd.RegisterEvent("--bresen_ham", [&](){rst->ShowBresen();});
    //     }else if(std::get<0>(command) == 3){
    //         std::shared_ptr<Rasterizer> rst = std::make_shared<Rasterizer>();
    //         cmd.RegisterEvent("--rst", [&](){rst->ShowRst();});
    //     }else{
    //         command = std::make_tuple(0, "--help", "");
    //     }
    //     cmd.Execute(std::get<1>(command), std::get<2>(command));
    // }
}
void Application::Destroy(){ }

int Application::exit(){
    Destroy();
    return 0;
}
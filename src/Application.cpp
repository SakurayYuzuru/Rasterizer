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
    int flag = 1;
    while(flag){
        auto [id, command, args] = arg.Execute();

        switch (id){
        case 0:
            cmd.Execute(command, args);
            break;
        case 1:
            rst = std::make_shared<Rasterizer>();
            rst->BindCamera(camera);
            rst->Execute();
            break;
        case 2:
            rst = std::make_shared<Rasterizer>();
            cmd.Execute(command, args);
            break;
        case 3:
            break;
        
        default:
            flag = exit();
            break;
        }
    }
}
void Application::Destroy(){ }

int Application::exit(){
    Destroy();
    return 0;
}
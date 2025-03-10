#include <Application.h>
#include <Mesh.h>
#include <LoadMeshCommand.h>

Application::Application(){
    Start();
}
Application::~Application(){
    Destroy();
}
void Application::Execute(){
    Update();

    if(arg.Execute()){
        this->rst = std::make_shared<Rasterizer>();
        rst->bindCamera(camera);
        rst->Execute();
    }else{
        exit();
    }
}

void Application::Start(){
    Mesh mesh;
    this->arg.AddOption("--model", std::make_unique<LoadMeshCommand>(mesh));
    this->camera = std::make_shared<Camera>();
}
void Application::Update(){ }
void Application::Destroy(){ }

int Application::exit(){
    Destroy();
    return 0;
}
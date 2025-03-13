#include <Application.h>
#include <Mesh.h>
#include <Texture.h>

#include <LoadMeshCommand.h>
#include <LoadTextureCommand.h>
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
    cmd.RegisterCommand("model", std::make_unique<LoadMeshCommand>(mesh));
    std::shared_ptr<Texture> texture = std::make_shared<Texture>();
    cmd.RegisterCommand("texture", std::make_unique<LoadTextureCommand>(texture));
    this->rst = std::make_shared<Rasterizer>();
    this->camera = std::make_shared<Camera>();
}
void Application::Update(){
    // rst->BindCamera(camera);
    // cmd.RegisterEvent("bresen_ham", [&](){rst->ShowBresen();});
    // cmd.Execute("bresen_ham", "");

    int flag = 1;
    while(flag){
        std::tuple<int, std::string, std::string> command = arg.Execute();
        
        if(std::get<0>(command) == -1){         // exit
            flag = exit();
        }else if(std::get<0>(command) == 2){    // bresen ham
            std::shared_ptr<Rasterizer> rst = std::make_shared<Rasterizer>();
            rst->BindCamera(camera);
            cmd.RegisterEvent(std::get<1>(command), [&](){rst->ShowBresen();});
        }else if(std::get<0>(command) == 3){    // rst
            std::shared_ptr<Rasterizer> rst = std::make_shared<Rasterizer>();
            rst->BindCamera(camera);
            cmd.RegisterEvent(std::get<1>(command), [&](){rst->ShowRst();});
        }else if(std::get<0>(command) == 4){    // model
            
        }else if(std::get<0>(command) == 5){    // texture

        }
        else{
            command = std::make_tuple(0, "help", "");
        }
        cmd.Execute(std::get<1>(command), std::get<2>(command));
    }
}
void Application::Destroy(){ }

int Application::exit(){
    Destroy();
    return 0;
}
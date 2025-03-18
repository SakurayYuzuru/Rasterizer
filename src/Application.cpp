#include <Application.h>
#include <Mesh.h>
#include <Texture.h>

#include <LoadMeshCommand.h>
#include <LoadTextureCommand.h>
#include <ShowBresenHamCommand.h>

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
    this->mesh = std::make_shared<Mesh>();
    this->cmd.RegisterCommand("model", std::make_unique<LoadMeshCommand>(mesh));
    this->texture = std::make_shared<Texture>();
    this->cmd.RegisterCommand("texture", std::make_unique<LoadTextureCommand>(texture));
    this->rst = std::make_shared<Rasterizer>();
    this->camera = std::make_shared<Camera>();
}
void Application::Update(){
    rst->BindCamera(camera);

    int flag = 1;
    while(flag){
        std::tuple<int, std::string, std::string> command = arg.Execute();
        
        if(std::get<0>(command) == -1){         // exit
            flag = exit();
        }else if(std::get<0>(command) == 1){
            this->rst->BindMesh(this->mesh);
            this->rst->BindTexture(this->texture);
            this->cmd.RegisterEvent(std::get<1>(command), [&](){rst->Execute();});
        }else if(std::get<0>(command) == 2){    // bresen ham
            this->cmd.RegisterEvent(std::get<1>(command), [&](){rst->ShowBresen();});
        }else if(std::get<0>(command) == 3){    // rst
            this->cmd.RegisterEvent(std::get<1>(command), [&](){rst->ShowRst();});
        }else if(std::get<0>(command) == 4){    // model
            // Load Model
        }else if(std::get<0>(command) == 5){    // texture
            // Load Texture
        }
        else{
            command = std::make_tuple(0, "help", "");
        }
        this->cmd.Execute(std::get<1>(command), std::get<2>(command));
    }
}
void Application::Destroy(){ }

int Application::exit(){
    Destroy();
    return 0;
}
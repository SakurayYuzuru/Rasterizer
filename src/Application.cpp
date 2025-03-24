#include <Application.h>

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
    this->texture = std::make_shared<Texture>();
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
            this->cmd.RegisterEvent(std::get<1>(command), [&](){this->rst->Execute();});
        }else if(std::get<0>(command) == 2){    // bresen ham
            this->cmd.RegisterEvent(std::get<1>(command), [&](){this->rst->ShowBresen();});
        }else if(std::get<0>(command) == 3){    // rst
            this->cmd.RegisterEvent(std::get<1>(command), [&](){this->rst->ShowRst();});
        }else if(std::get<0>(command) == 4){    // model
            // Load Model
            this->cmd.RegisterEvent(std::get<1>(command), [&](){this->mesh->LoadMesh(std::get<2>(command));});
        }else if(std::get<0>(command) == 5){    // texture
            // Load Texture
            this->cmd.RegisterEvent(std::get<1>(command), [&](){this->texture->LoadTexture(std::get<2>(command));});
        }else if(std::get<0>(command) == 6){
            this->cmd.RegisterEvent(std::get<1>(command), [&](){this->rst->SetShader(std::get<2>(command));});
        }else{
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
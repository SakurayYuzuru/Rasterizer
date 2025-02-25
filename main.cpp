#include <Rasterizer.h>
#include <Camera.h>

#include <iostream>
#include <vector>
#include <memory>
#include <exception>

int main(int argc, char* argv[]){
    std::shared_ptr<Rasterizer> rst = std::make_shared<Rasterizer>();
    std::shared_ptr<Camera> camera = std::make_shared<Camera>();
    std::vector<std::shared_ptr<IManager>> managers;

    managers.push_back(camera);
    managers.push_back(rst);

    while(!rst->isQuit()){
        for(auto &manager : managers){
            if(manager.get() == camera.get()){
                rst->bindCamera(camera);
            }
            manager->Update();
        }
    }

    return 0;
}
#include <Rasterizer.h>
#include <Camera.h>

#include <iostream>
#include <vector>
#include <memory>
#include <exception>

int main(int argc, char* argv[]){
    std::shared_ptr<Rasterizer> rst = std::make_shared<Rasterizer>();
    std::shared_ptr<Camera> camera = std::make_shared<Camera>();

    while(!rst->isQuit()){
        rst->bindCamera(camera);
        rst->Update();
    }

    return 0;
}
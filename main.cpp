#include <Rasterizer.h>
#include <Camera.h>

#include <iostream>
#include <vector>
#include <memory>
#include <exception>

// int main(int argc, char* argv[]){
//     Rasterizer *rst = new Rasterizer();
//     Camera *camera = new Camera();

//     std::vector<IManager*> managers;
//     managers.push_back(rst);
//     managers.push_back(camera);

//     while(!rst->isQuit()){
//         for(auto &manager : managers){
//             if(manager == rst){
//                 rst->set_view(camera->getViewMatrix());
//             }

//             manager->Update();
//         }
//     }

//     return 0;
// }

int main(int argc, char* argv[]){
    std::shared_ptr<Rasterizer> rst = std::make_shared<Rasterizer>();
    std::shared_ptr<Camera> camera = std::make_shared<Camera>();
    std::vector<std::shared_ptr<IManager>> managers;

    managers.push_back(rst);
    managers.push_back(camera);

    while(!rst->isQuit()){
        for(auto &manager : managers){
            if(manager.get() == rst.get()){
                rst->set_view(camera->getViewMatrix());
            }

            manager->Update();
        }
    }

    return 0;
}
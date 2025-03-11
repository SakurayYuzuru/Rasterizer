#include <ShowBresenHam.h>

ShowBresenHam::ShowBresenHam(){ }
ShowBresenHam::~ShowBresenHam(){ }

void ShowBresenHam::Execute(const std::string& arg){
    std::shared_ptr<Rasterizer> rst = std::make_shared<Rasterizer>(Rasterizer::GetInstance());
    rst->ShowBresen();
}
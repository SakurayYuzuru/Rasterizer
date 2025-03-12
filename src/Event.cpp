#include <Event.h>

void Event::Invoke(){
    for(const auto& handler : handlers){
        handler();
    }
}
void Event::Subscribe(Handler handler){
    handlers.push_back(handler);
}
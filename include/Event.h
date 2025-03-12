#ifndef EVENT_H
#define EVENT_H

#pragma once

#include <vector>
#include <functional>

class Event{
public:
    using Handler = std::function<void()>;

    void Invoke();
    void Subscribe(Handler handler);

private:
    std::vector<Handler> handlers;
};

#endif
#ifndef IMANAGER_H
#define IMANAGER_H

#pragma once

#include <SDL2/SDL.h>

class IManager{
protected:
    virtual ~IManager() = default;

    virtual void Start() = 0;
    virtual void Update() = 0;
    virtual void Destroy() = 0;
};

#endif
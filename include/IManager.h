#pragma once

class IManager{
public:
    virtual ~IManager() = default;

    virtual void Start() = 0;
    virtual void Update() = 0;
    virtual void Destroy() = 0;
};
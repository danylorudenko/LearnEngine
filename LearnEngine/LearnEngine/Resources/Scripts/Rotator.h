#pragma once

#include "..\..\Include\RenderingSystem\Camera.h"
#include "F:\Git_local\LearnOpenGL\LearnEngine\LearnEngine\Include\Component\Script\Script.h"

class Rotator :
    public Script
{
public:
    Rotator();

protected:
    virtual void Tick() override;
    virtual void OnRegistered() override;

    virtual ~Rotator() override { };

    Camera* cam;
};


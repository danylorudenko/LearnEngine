#pragma once

#include "..\..\Include\Component\GLObject\GLObject.h"
#include "..\..\Include\RenderingSystem\Camera.h"
#include "..\..\Include\Component\Script\Script.h"

class Rotator :
    public Script
{
public:
    Rotator();

protected:
    virtual void Tick() override;
    virtual void OnRegistered() override;

    virtual ~Rotator() override { };

    float y_rotation_;
};


#ifndef __ROTATOR_H__
#define __ROTATOR_H__

#include "..\..\Include\Component\GLObject\GLObject.h"
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

#endif
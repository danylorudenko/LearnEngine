#ifndef __ROTATOR_H__
#define __ROTATOR_H__

#include <Engine\Component\GLObject\GLObject.h>
#include <Engine\Component\Script\Script.h>

class Rotator :
    public Script
{
public:
    Rotator();

protected:
    virtual void Tick() override;

    virtual ~Rotator() override { };

    float y_rotation_;
};

#endif
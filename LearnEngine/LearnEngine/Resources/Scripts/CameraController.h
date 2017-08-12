#ifndef __CAMERA_CONTROLLER_H__
#define __CAMERA_CONTROLLER_H__

#include "..\..\Include\Component\Script\Script.h"

class CameraController : public Script
{
public:
    CameraController();

    virtual ~CameraController() { }

protected:
    virtual void Tick() override;

    bool cursor_on_;
};

#endif
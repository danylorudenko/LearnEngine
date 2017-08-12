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

    float x_rotation_;
    float y_rotation_;

    bool cursor_on_;
};

#endif
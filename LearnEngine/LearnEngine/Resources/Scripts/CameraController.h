#ifndef __CAMERA_CONTROLLER_H__
#define __CAMERA_CONTROLLER_H__

#include <Engine\Component\Script\Script.h>

class CameraController : public Engine::Script
{
public:
    CameraController();

    virtual ~CameraController() { }

protected:
    virtual void Tick() override;

    void SetNewRotation();
    void SetNewPosition();

    float x_rotation_;
    float y_rotation_;

    bool cursor_on_;
};

#endif
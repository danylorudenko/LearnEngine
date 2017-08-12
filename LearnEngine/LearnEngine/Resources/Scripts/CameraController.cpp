#include <iostream>

#include "CameraController.h"
#include "..\..\Include\Input\InputSystem.h"

CameraController::CameraController() :
    x_rotation_(0.0f),
    y_rotation_(0.0f),
    cursor_on_(true)
{
    SetTicking(true);
}

void CameraController::Tick()
{
    if (InputSystem::Instance().GetKeyDown(GLFW_KEY_C)) {
        switch(cursor_on_) 
        {
        case true:
            InputSystem::Instance().DisableCursor();
            cursor_on_ = false;
            break;
        case false:
            InputSystem::Instance().EnableCursor();
            cursor_on_ = true;
            break;
        }
    }
    
    static constexpr float ROT_SPEED = 0.1f;

    auto mouse_delta = InputSystem::Instance().GetMouseDelta() * ROT_SPEED;
    x_rotation_ += mouse_delta.x;
    y_rotation_ += mouse_delta.y;
    owner_->Transform().SetRotation(y_rotation_, x_rotation_, 0.0f);

}
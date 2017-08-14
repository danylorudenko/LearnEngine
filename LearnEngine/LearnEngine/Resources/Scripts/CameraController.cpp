#include <iostream>

#include "CameraController.h"
#include "..\..\Include\Input\InputSystem.h"
#include "..\..\Include\Program\Program.h"


CameraController::CameraController() :
    x_rotation_(0.0f),
    y_rotation_(0.0f),
    cursor_on_(false)
{
    SetTicking(true);
    InputSystem::Instance().DisableCursor();
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
    
    SetNewRotation();
    SetNewPosition();

}

void CameraController::SetNewRotation()
{
    static constexpr float ROT_SPEED = 0.1f;

    auto mouse_delta = InputSystem::Instance().GetMouseDelta() * ROT_SPEED;
    x_rotation_ += mouse_delta.x;
    y_rotation_ += mouse_delta.y;
    owner_->Transform().SetRotation(y_rotation_, x_rotation_, 0.0f);
}

void CameraController::SetNewPosition()
{
    
    if (InputSystem::Instance().GetKeyDown(GLFW_KEY_ESCAPE)) {
        Program::Instance().Close();
    }
    
    auto pos_local = owner_->Transform().GetPosition();
    
    static constexpr float MOV_SPEED = 0.01f;

    if (InputSystem::Instance().GetKey(GLFW_KEY_W)) {
        pos_local += owner_->Transform().Forward() * MOV_SPEED;
    }
    if (InputSystem::Instance().GetKey(GLFW_KEY_S)) {
        pos_local -= owner_->Transform().Forward() * MOV_SPEED;
    }
    if (InputSystem::Instance().GetKey(GLFW_KEY_A)) {
        pos_local += owner_->Transform().Right() * MOV_SPEED;
    }
    if (InputSystem::Instance().GetKey(GLFW_KEY_D)) {
        pos_local -= owner_->Transform().Right() * MOV_SPEED;
    }

    owner_->Transform().SetPosition(pos_local);
}

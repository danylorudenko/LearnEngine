#include <iostream>

#include "CameraController.h"
#include "..\..\Include\Input\InputSystem.h"

CameraController::CameraController() :
    cursor_on_(true)
{
    SetTicking(true);
}

void CameraController::Tick()
{
    if (InputSystem::Instance().GetKeyDown(GLFW_KEY_C)) {
        if (cursor_on_) {
            InputSystem::Instance().DisableCursor();
            cursor_on_ = false;
        }
        else {
            InputSystem::Instance().EnableCursor();
            cursor_on_ = true;
        }
    }
    
    auto delta = InputSystem::Instance().GetMouseDelta();
    std::cout << delta.x << " " << delta.y << std::endl;
}
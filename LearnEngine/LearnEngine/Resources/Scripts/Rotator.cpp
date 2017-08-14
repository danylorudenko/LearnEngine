#include "Rotator.h"
#include "..\..\Include\Input\InputSystem.h"
#include "..\..\Include\Entity\Entity.h"
#include "..\..\Include\Program\Program.h"
#include <iostream>

static glm::quat rot_delta(glm::vec3(0.003f, 0.001f, 0));

Rotator::Rotator() :
    y_rotation_(0.0f)
{
    SetTicking(true);
}

void Rotator::Tick()
{
    //owner_->Transform().SetRotation(y_type(), y_rotation_);
    //owner_->Transform().SetRotation(z_type(), y_rotation_);
    //owner_->Transform().SetRotation(x_type(), y_rotation_ * 2);
    //y_rotation_ += 0.1f;

    owner_->Transform().Rotation() *= rot_delta;
    
    /*auto old_pos = owner_->Transform().GetPosition();
    if (InputSystem::Instance().GetKey(GLFW_KEY_A)) {
        owner_->Transform().SetPosition(x_type(), old_pos.x + 0.01f);
    }

    if (InputSystem::Instance().GetKey(GLFW_KEY_D)) {
        owner_->Transform().SetPosition(x_type(), old_pos.x - 0.01f);
    }

    if (InputSystem::Instance().GetKey(GLFW_KEY_W)) {
        owner_->Transform().SetPosition(z_type(), old_pos.z + 0.01f);
    }

    if (InputSystem::Instance().GetKey(GLFW_KEY_S)) {
        owner_->Transform().SetPosition(z_type(), old_pos.z - 0.01f);
    }

    if (InputSystem::Instance().GetKey(GLFW_KEY_SPACE)) {
        owner_->Transform().SetPosition(y_type(), old_pos.y + 0.01f);
    }

    if (InputSystem::Instance().GetKey(GLFW_KEY_LEFT_CONTROL)) {
        owner_->Transform().SetPosition(y_type(), old_pos.y - 0.01f);
    }

    if (InputSystem::Instance().GetKey(GLFW_KEY_ESCAPE)) {
        Program::Instance().Close();
    }*/

    //auto new_pos = owner_->Transform().GetPosition();
    //auto new_pos = InputSystem::Instance().GetMousePos();
    //std::cout << new_pos.x << ", " << new_pos.y << ", " /*<< new_pos.z*/ << std::endl;
}
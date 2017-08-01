#include "Rotator.h"
#include "..\..\Include\Input\InputSystem.h"
#include "..\..\Include\Entity\Entity.h"
#include "..\..\Include\Program\Program.h"
#include <iostream>

Rotator::Rotator() :
    y_rotation_(0.0f)
{
}

void Rotator::OnRegistered()
{
    owner_->Transform().SetScale(glm::vec3(0.3f));
    owner_->Transform().SetPosition(glm::vec3(0.0f, -0.5f, 3.0f));
    SetTicking(true);
}


void Rotator::Tick()
{
    owner_->Transform().SetRotation(y_type(), y_rotation_);
    owner_->Transform().SetRotation(z_type(), y_rotation_ / 2.0f);
    owner_->Transform().SetRotation(x_type(), y_rotation_ * 2);
    y_rotation_ += 1.1f;
    
    auto old_pos = owner_->Transform().GetPosition();
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
    }

    auto new_pos = owner_->Transform().GetPosition();
    std::cout << new_pos.x << ", " << new_pos.y << ", " << new_pos.z << std::endl;
}
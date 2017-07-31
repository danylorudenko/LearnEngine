#include "Rotator.h"
#include "..\..\Include\Input\InputSystem.h"
#include "..\..\Include\Entity\Entity.h"
#include <iostream>

Rotator::Rotator() : 
    target_(nullptr),
    y_rotation_(0.0f)
{
}

void Rotator::OnRegistered()
{
    target_ = owner_->GetComponent<GLObject>();
    target_->SetScale(glm::vec3(0.3f));
    target_->SetPosition(glm::vec3(0.0f, -0.5f, 3.0f));
    SetTicking(true);
}


void Rotator::Tick()
{
    target_->SetRotation(y_type(), y_rotation_);
    y_rotation_ += 1.1f;
    
    auto old_pos = target_->GetPosition();
    if (InputSystem::Instance().GetKey(GLFW_KEY_A)) {
        target_->SetPosition(x_type(), old_pos.x + 0.01f);
    }

    if (InputSystem::Instance().GetKey(GLFW_KEY_D)) {
        target_->SetPosition(x_type(), old_pos.x - 0.01f);
    }

    if (InputSystem::Instance().GetKey(GLFW_KEY_W)) {
        target_->SetPosition(z_type(), old_pos.z + 0.01f);
    }

    if (InputSystem::Instance().GetKey(GLFW_KEY_S)) {
        target_->SetPosition(z_type(), old_pos.z - 0.01f);
    }

    if (InputSystem::Instance().GetKey(GLFW_KEY_SPACE)) {
        target_->SetPosition(y_type(), old_pos.y + 0.01f);
    }

    if (InputSystem::Instance().GetKey(GLFW_KEY_LEFT_CONTROL)) {
        target_->SetPosition(y_type(), old_pos.y - 0.01f);
    }

    auto new_pos = target_->GetPosition();
    std::cout << new_pos.x << ", " << new_pos.y << ", " << new_pos.z << std::endl;
}
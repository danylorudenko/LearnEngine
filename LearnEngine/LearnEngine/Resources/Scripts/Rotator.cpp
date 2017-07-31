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
    target_->SetScale(glm::vec3(2.f));
    target_->SetPosition(glm::vec3(0.0f, -0.5f, 3.0f));
    SetTicking(true);
}


void Rotator::Tick()
{
    //target_->SetRotation(y_type(), y_rotation_);
    y_rotation_ += 0.01f;
    
    auto old_pos = target_->GetRotation();
    if (InputSystem::Instance().GetKey(GLFW_KEY_A)) {
        target_->SetRotation(x_type(), old_pos.x + 1.01f);
    }

    if (InputSystem::Instance().GetKey(GLFW_KEY_D)) {
        target_->SetRotation(x_type(), old_pos.x - 1.01f);
    }

    if (InputSystem::Instance().GetKey(GLFW_KEY_W)) {
        target_->SetRotation(y_type(), old_pos.y + 1.01f);
    }

    if (InputSystem::Instance().GetKey(GLFW_KEY_S)) {
        target_->SetRotation(y_type(), old_pos.y - 1.01f);
    }

    auto new_pos = target_->GetPosition();
    std::cout << new_pos.x << ", " << new_pos.y << ", " << new_pos.z << std::endl;
}
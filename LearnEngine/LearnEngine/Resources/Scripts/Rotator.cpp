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
    target_->SetScale(glm::vec3(4.0f));
    SetTicking(true);
}


void Rotator::Tick()
{
    auto old_pos = target_->GetPosition();
    if (InputSystem::Instance().GetKey(GLFW_KEY_D)) {
        target_->SetPosParam(x_type(), old_pos.x + 0.01f);
    }

    if (InputSystem::Instance().GetKey(GLFW_KEY_A)) {
        target_->SetPosParam(x_type(), old_pos.x - 0.01f);
    }

    auto new_pos = target_->GetPosition();
    std::cout << new_pos.x << ", " << new_pos.y << ", " << new_pos.z << std::endl;
    
    target_->SetRotParam(y_type(), y_rotation_);
    y_rotation_ += 0.3f;
}
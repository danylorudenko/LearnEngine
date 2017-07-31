#include "Rotator.h"
#include "..\..\Include\RenderingSystem\RenderingSystem.h"
#include "..\..\Include\Input\InputSystem.h"
#include <glm\gtx\rotate_vector.hpp>
#include "..\..\Include\Entity\Entity.h"

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
    if (InputSystem::Instance().GetKey(GLFW_KEY_D)) {
        target_->SetPosParam(x_type(), target_->GetPosition().x + 0.01f);
    }

    if (InputSystem::Instance().GetKey(GLFW_KEY_A)) {
        target_->SetPosParam(x_type(), target_->GetPosition().x - 0.01f);
    }
    
    target_->SetRotParam(y_type(), y_rotation_);
    y_rotation_ += 0.3f;
}
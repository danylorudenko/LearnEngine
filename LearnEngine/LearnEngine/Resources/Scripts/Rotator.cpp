#include <iostream>

#include <Engine\Input\InputSystem.h>
#include <Engine\Entity\Entity.h>
#include <Engine\Program\Program.h>

#include "Rotator.h"

static glm::quat rot_delta(glm::vec3(0.0f, 0.008f, 0.002f));
//static float x_rotation_ = 0.0f;

Rotator::Rotator() :
    y_rotation_(0.0f)
{
    SetTicking(true);
}

void Rotator::Tick()
{
    owner_->Transform().Rotation() *= rot_delta;
}
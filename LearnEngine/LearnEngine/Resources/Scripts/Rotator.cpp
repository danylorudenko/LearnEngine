#include "Rotator.h"
#include "..\..\Include\Input\InputSystem.h"
#include "..\..\Include\Entity\Entity.h"
#include "..\..\Include\Program\Program.h"
#include <iostream>

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
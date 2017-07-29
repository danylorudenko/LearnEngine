#include "Rotator.h"
#include "..\..\Include\RenderingSystem\RenderingSystem.h"
#include <glm\gtx\rotate_vector.hpp>


Rotator::Rotator() : cam(nullptr)
{
}

void Rotator::OnRegistered()
{
    cam = &(RenderingSystem::Instance().GetMainCamera());
    
    SetTicking(true);
}


void Rotator::Tick()
{
    auto currentDir = cam->GetViewDirection();
    glm::rotateY(currentDir, 3.0f);
}
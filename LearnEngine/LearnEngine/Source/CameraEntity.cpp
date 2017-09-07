#include <glm\vec3.hpp>
#include <glm\mat4x4.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include <Engine\World\World.h>
#include <Engine\Entity\CameraEntity.h>

namespace Engine
{

CameraEntity::CameraEntity(Entity* parent) : 
    Entity(parent),
    fow_(60.0f),
    transform_(new GLTransform())
{
    name_ = "new_camera_entity";
    clipping_planes_[0] = 0.1f;
    clipping_planes_[1] = 1000.0f;
}

CameraEntity::~CameraEntity()
{
    
}

CameraEntity * CameraEntity::CreateCamera()
{
    CameraEntity* new_entity = new CameraEntity(&World::Instance().Root());
    return new_entity;
}

GLfloat CameraEntity::GetFOW() const
{
    return fow_;
}

GLfloat& CameraEntity::GetFOW()
{
    return fow_;
}

const GLfloat* CameraEntity::GetClippingPlanes() const
{
    return (GLfloat*)clipping_planes_;
}

} // namespace Engine

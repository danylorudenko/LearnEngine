#include <glm\vec3.hpp>
#include <glm\mat4x4.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include "..\Include\RenderingSystem\Camera.h"

Camera::Camera(const GLfloat fow) : 
    fow_(fow),
    world_position_(new glm::vec3(0.0f)),
    view_direction_(new glm::vec3(0.0f))
{
    clipping_planes_[0] = 0.1f;
    clipping_planes_[1] = 1000.0f;
}

Camera::~Camera()
{
    delete world_position_;
    delete view_direction_;
}

void Camera::SetWorldPosition(glm::vec3 & pos)
{
	*world_position_ = pos;
}

void Camera::SetViewDirection(glm::vec3 & dir)
{
	*view_direction_ = glm::normalize(dir);
}

glm::vec3 Camera::GetWorldPosition() const
{
    return *world_position_;
}

glm::vec3 Camera::GetViewDirection() const
{
    return *view_direction_;
}

GLfloat Camera::GetFOW() const
{
    return fow_;
}

GLfloat* Camera::GetClippingPlanes() const
{
    return (GLfloat*)clipping_planes_;
}

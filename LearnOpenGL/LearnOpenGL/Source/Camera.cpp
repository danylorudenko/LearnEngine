#include <glm\vec3.hpp>

#include "..\Include\Camera.h"

Camera::Camera(const GLfloat aspect_ratio, const GLfloat fow) : 
    aspect_ratio_(aspect_ratio), 
    fow_(fow),
    world_position_(new glm::vec3()),
    view_direction_(new glm::vec3())
{

}

Camera::~Camera()
{
    delete world_position_;
    delete view_direction_;
}
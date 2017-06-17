#include <glm\vec3.hpp>
#include <glm\mat4x4.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include "..\Include\Camera.h"

Camera::Camera(const GLfloat width, const GLfloat height, const GLfloat fow) : 
    aspect_ratio_(width / height), 
    fow_(fow),
    world_position_(new glm::vec3(0.0f)),
    view_direction_(new glm::vec3(0.0f))
{

}

Camera::~Camera()
{
    delete world_position_;
    delete view_direction_;
}

glm::mat4 Camera::GetViewMatrix() const
{
    return glm::lookAt(*view_direction_, *world_position_, glm::vec3(1.0f, 0.0f, 0.0f));
}

glm::mat4 Camera::GetPerspectiveMatrix() const
{
    return glm::perspective(glm::radians(fow_), aspect_ratio_, 0.1f, 100.0f);
}

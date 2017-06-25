#include <glm\vec3.hpp>
#include <glm\mat4x4.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include "..\Include\RenderingSystem\Camera.h"

Camera::Camera(const GLfloat fow) : 
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

glm::mat4 Camera::GetPerspectiveMatrix(int viewport_width, int viewport_height) const
{
    float aspect_ratio = static_cast<float>(viewport_width) / static_cast<float>(viewport_height);
    return glm::perspective(glm::radians(fow_), aspect_ratio, 0.1f, 100.0f);
}

void Camera::SetWorldPosition(glm::vec3 & pos)
{
	*world_position_ = pos;
}

void Camera::SetViewDirection(glm::vec3 & dir)
{
	*view_direction_ = dir;
}

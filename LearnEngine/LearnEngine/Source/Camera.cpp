#include <glm\vec3.hpp>
#include <glm\mat4x4.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include "..\Include\RenderingSystem\Camera.h"

Camera::Camera(const GLfloat fow) : 
    fow_(fow),
    transform_(new GLTransform())
{
    clipping_planes_[0] = 0.1f;
    clipping_planes_[1] = 1000.0f;
}

Camera::~Camera()
{
    
}

GLfloat Camera::GetFOW() const
{
    return fow_;
}

GLTransform & Camera::Transform()
{
    return *transform_;
}

const GLfloat* Camera::GetClippingPlanes() const
{
    return (GLfloat*)clipping_planes_;
}

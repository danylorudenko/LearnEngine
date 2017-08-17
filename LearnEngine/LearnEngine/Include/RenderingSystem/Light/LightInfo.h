#ifndef __LIGHT_INFO_STRUCT_H__
#define __LIGHT_INFO_STRUCT_H__

#include <GL\glew.h>
#include <glm\gtc\quaternion.hpp>

struct LightInfo
{
    glm::vec3   color;
    glm::vec3   position;
    glm::quat   rotation;
    GLfloat     range;
    GLfloat     intensity;
};

#endif
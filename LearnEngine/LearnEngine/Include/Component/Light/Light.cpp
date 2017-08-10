#include "Light.h"

Light::Light()
{
}

GLfloat Light::GetIntensity() const
{
    return intensity_;
}

GLfloat Light::GetRange() const
{
    return range_;
}

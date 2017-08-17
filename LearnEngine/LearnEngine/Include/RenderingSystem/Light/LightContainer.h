#ifndef __LIGHT_CONTAINER_H__
#define __LIGHT_CONTAINER_H__

#include <GLFW\glfw3.h>
#include <list>

#include "..\..\Texture\TextureController.h"
#include "..\..\Component\Light\Light.h"

class LightContainer
{
public:

    static constexpr GLsizei Y_SIZE = 3;

    using LightList = std::list<Light>;

    LightContainer                          ();

    LightContainer                          (const LightContainer& rhs) = delete;
    LightContainer                          (LightContainer&& rhs) = delete;
    LightContainer&     operator=           (const LightContainer& rhs) = delete;
    LightContainer&     operator=           (LightContainer&& rhs) = delete;

    ~LightContainer                         ();

protected:


protected:
    TextureController   texture_controller_;
};

#endif
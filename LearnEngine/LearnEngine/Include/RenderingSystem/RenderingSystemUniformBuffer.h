#ifndef __RENDERING_SYSTEM_UNIFORM_BUFFER_H__
#define __RENDERING_SYSTEM_UNIFORM_BUFFER_H__

#include <GL\glew.h>
#include <glm\mat4x4.hpp>
#include <glm\vec3.hpp>
#include "..\Util\Singletone.h"

class RenderingSystemUniformBuffer : public Singletone<RenderingSystemUniformBuffer>
{
public:
    static constexpr GLuint     RENDERING_SYSTEM_UNIFORM_BINDING_IDNEX = 0;
protected:
    static constexpr GLsizei    BUFFER_SIZE             = sizeof(glm::mat4) 
                                                        + sizeof(glm::mat4)
                                                        + sizeof(glm::vec3);

    RenderingSystemUniformBuffer                        ();
    RenderingSystemUniformBuffer                        (const RenderingSystemUniformBuffer& rhs) = delete;
    RenderingSystemUniformBuffer                        (RenderingSystemUniformBuffer&& rhs) = delete;
    RenderingSystemUniformBuffer        operator=       (const RenderingSystemUniformBuffer& rhs) = delete;
    RenderingSystemUniformBuffer        operator=       (RenderingSystemUniformBuffer&& rhs) = delete;


protected:
    void            AllocateGPUBuffer           ();

protected:
    GLuint          uniform_buffer_handle_;
};

#endif
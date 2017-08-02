#ifndef __RENDERING_SYSTEM_UNIFORM_BUFFER_H__
#define __RENDERING_SYSTEM_UNIFORM_BUFFER_H__

#include <GL\glew.h>
#include <glm\mat4x4.hpp>
#include <glm\vec3.hpp>
#include "..\Util\Singletone.h"
#include "..\Entity\CameraEntity.h"

// Wrapper for conventional RenderingSystem uniform buffer.
// Rendering system is responisble for putting data in this buffer, it is persistent across single rendering iteration.
class RenderingSystemUniformBuffer
{
protected:
    static constexpr GLuint     RENDERING_SYSTEM_UNIFORM_BINDING_IDNEX = 0;
    static constexpr GLsizei    BUFFER_SIZE             = sizeof(glm::mat4)  // viewMatrix
                                                        + sizeof(glm::mat4)  // perspectiveMatrix
                                                        + sizeof(glm::vec3)  // cameraPos
                                                        + sizeof(glm::vec3); // cameraRot

public:
    RenderingSystemUniformBuffer                        ();
    RenderingSystemUniformBuffer                        (const RenderingSystemUniformBuffer& rhs) = delete;
    RenderingSystemUniformBuffer                        (RenderingSystemUniformBuffer&& rhs) = delete;
    RenderingSystemUniformBuffer        operator=       (const RenderingSystemUniformBuffer& rhs) = delete;
    RenderingSystemUniformBuffer        operator=       (RenderingSystemUniformBuffer&& rhs) = delete;

    // Bind buffer to the conventional target for the rendering system main uniform block.
    void            Bind                                () const;

    // Update buffer with new data from the camera.
    void            UpdateCameraData                    (const CameraEntity& camera, GLfloat aspect_ratio);

protected:
    // Allocate GPU buffer to hold rendering system main unifrom block buffer.
    void            AllocateGPUBuffer                   ();
    
protected:
    GLuint          uniform_buffer_handle_;
};

#endif
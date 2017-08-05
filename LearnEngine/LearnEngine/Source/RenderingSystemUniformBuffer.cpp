#include "..\Include\RenderingSystem\RenderingSystemUniformBuffer.h"
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include "..\Include\Util\Debugging\DebugTools.h"

RenderingSystemUniformBuffer::RenderingSystemUniformBuffer() :
    uniform_buffer_handle_(0)
{
    AllocateGPUBuffer();
}

void RenderingSystemUniformBuffer::Bind() const
{
    glBindBufferBase(GL_UNIFORM_BUFFER, RENDERING_SYSTEM_UNIFORM_BINDING_IDNEX, uniform_buffer_handle_);
}

void RenderingSystemUniformBuffer::UpdateCameraData(
    const CameraEntity& camera, GLfloat aspect_ratio)
{
    // TODO: add roll support(around z coordinate)
    // Camera view direction calculation ( x = yaw, y = pitch)

    auto rotation = camera.Transform().GetRotation();
    GLfloat short_hypothenuse = std::cosf(glm::radians(rotation.x));
    glm::vec3 direction(
        std::sinf(glm::radians(rotation.y)) * short_hypothenuse,
        std::sinf(glm::radians(rotation.x)),
        std::cosf(glm::radians(rotation.y)) * short_hypothenuse
    );

    glm::mat4 view_matrix = glm::lookAt(
        camera.Transform().GetPosition(), 
        direction + camera.Transform().GetPosition(), 
        glm::vec3(0.0f, 1.0f, 0.0f));

    glm::mat4 perspective_matrix = glm::perspective(
        glm::radians(camera.GetFOW()), 
        aspect_ratio, 
        camera.GetClippingPlanes()[0], 
        camera.GetClippingPlanes()[1]);

#ifdef GL44

    glBindBuffer(GL_UNIFORM_BUFFER, uniform_buffer_handle_);
    GLubyte* buffer_data = (GLubyte*)glMapBuffer(GL_UNIFORM_BUFFER, GL_WRITE_ONLY);

    display_gl_errors();

#else

    GLubyte* buffer_data = (GLubyte*)glMapNamedBuffer(uniform_buffer_handle_, GL_WRITE_ONLY);

#endif

    std::memcpy(buffer_data, &view_matrix, sizeof(view_matrix));
    buffer_data += sizeof(view_matrix);

    std::memcpy(buffer_data, &perspective_matrix, sizeof(perspective_matrix));
    buffer_data += sizeof(perspective_matrix);

    std::memcpy(buffer_data, &camera.Transform().GetPosition(), sizeof(camera.Transform().GetPosition()));
    buffer_data += sizeof(camera.Transform().GetPosition());

    std::memcpy(buffer_data, &rotation, sizeof(rotation));

#ifdef GL44

    glUnmapBuffer(GL_UNIFORM_BUFFER);

    display_gl_errors();

#else

    glUnmapNamedBuffer(uniform_buffer_handle_);

#endif

    
}

void RenderingSystemUniformBuffer::AllocateGPUBuffer()
{
    static const glm::mat4 identity_matrix(
        glm::vec4(1.0f, 0.0f, 0.0f, 0.0f),
        glm::vec4(0.0f, 1.0f, 0.0f, 0.0f),
        glm::vec4(0.0f, 0.0f, 1.0f, 0.0f),
        glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)
    );

    static const glm::vec3 zero_vector(0.0f);

    glCreateBuffers(1, &uniform_buffer_handle_);

#ifdef GL44

    glBindBuffer(GL_UNIFORM_BUFFER, uniform_buffer_handle_);

    glBufferStorage(
        GL_UNIFORM_BUFFER,
        BUFFER_SIZE,
        nullptr,
        GL_DYNAMIC_STORAGE_BIT | GL_MAP_READ_BIT | GL_MAP_WRITE_BIT
    );

    display_gl_errors();

    // viewMatrix
    glBufferSubData(
        GL_UNIFORM_BUFFER,
        0,
        sizeof(identity_matrix),
        glm::value_ptr(identity_matrix)
    );

    // perspectiveMatrix
    glBufferSubData(
        GL_UNIFORM_BUFFER,
        sizeof(decltype(identity_matrix)),
        sizeof(decltype(identity_matrix)),
        glm::value_ptr(identity_matrix)
    );

    // camera position
    glBufferSubData(
        GL_UNIFORM_BUFFER,
        sizeof(identity_matrix) + sizeof(identity_matrix),
        sizeof(zero_vector),
        glm::value_ptr(zero_vector)
    );

    // camera rotation
    glBufferSubData(
        GL_UNIFORM_BUFFER,
        sizeof(identity_matrix) + sizeof(identity_matrix) + sizeof(zero_vector),
        sizeof(zero_vector),
        glm::value_ptr(zero_vector)
    );

    display_gl_errors();

#else

    glNamedBufferStorage(
        uniform_buffer_handle_,
        BUFFER_SIZE,
        nullptr,
        GL_DYNAMIC_STORAGE_BIT | GL_MAP_READ_BIT | GL_MAP_WRITE_BIT
    );

    // viewMatrix
    glNamedBufferSubData(
        uniform_buffer_handle_,
        0,
        sizeof(identity_matrix),
        glm::value_ptr(identity_matrix)
    );

    // perspectiveMatrix
    glNamedBufferSubData(
        uniform_buffer_handle_,
        sizeof(decltype(identity_matrix)),
        sizeof(decltype(identity_matrix)),
        glm::value_ptr(identity_matrix)
    );

    // camera position
    glNamedBufferSubData(
        uniform_buffer_handle_,
        sizeof(identity_matrix) + sizeof(identity_matrix),
        sizeof(zero_vector),
        glm::value_ptr(zero_vector)
    );

    // camera rotation
    glNamedBufferSubData(
        uniform_buffer_handle_,
        sizeof(identity_matrix) + sizeof(identity_matrix) + sizeof(zero_vector),
        sizeof(zero_vector),
        glm::value_ptr(zero_vector)
    );

#endif
}

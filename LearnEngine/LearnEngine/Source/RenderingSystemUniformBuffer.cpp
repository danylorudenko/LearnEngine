#include "..\Include\RenderingSystem\RenderingSystemUniformBuffer.h"
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include "..\Include\Util\Debugging\DebugTools.h"

RenderingSystemUniformBuffer::RenderingSystemUniformBuffer() :
    uniform_buffer_handle_(0)
{
    AllocateGPUBuffer();
}

RenderingSystemUniformBuffer::~RenderingSystemUniformBuffer()
{
    DestroyGPUBuffer();
}

void RenderingSystemUniformBuffer::Bind() const
{
    glBindBufferBase(GL_UNIFORM_BUFFER, RENDERING_SYSTEM_UNIFORM_BINDING_IDNEX, uniform_buffer_handle_);
}

void RenderingSystemUniformBuffer::UpdateCameraData(
    const CameraEntity& camera, GLfloat aspect_ratio)
{
    glm::vec3 direction = glm::mat4_cast(camera.Transform().Rotation()) * glm::vec4(1.0f, 0.0f, 0.0f, 0.0f);

    glm::mat4 view_matrix = glm::lookAt(
        camera.Transform().Position(), 
        camera.Transform().Position() + camera.Transform().Forward(), 
        camera.Transform().Up());

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

    GLubyte* buffer_data = 
        (GLubyte*)glMapNamedBufferRange(
            uniform_buffer_handle_,
            0,
            sizeof(glm::mat4) * 2 + sizeof(glm::vec3) * 2,
            GL_WRITE_ONLY
            );

#endif

    std::memcpy(buffer_data, &view_matrix, sizeof(view_matrix));
    buffer_data += sizeof(view_matrix);

    std::memcpy(buffer_data, &perspective_matrix, sizeof(perspective_matrix));
    buffer_data += sizeof(perspective_matrix);

    std::memcpy(buffer_data, &camera.Transform().Position(), sizeof(camera.Transform().Position()));
    buffer_data += sizeof(camera.Transform().Position());

    std::memcpy(buffer_data, &camera.Transform().Euler(), sizeof(camera.Transform().Euler()));

#ifdef GL44

    glUnmapBuffer(GL_UNIFORM_BUFFER);

    display_gl_errors();

#else

    glUnmapNamedBuffer(uniform_buffer_handle_);

#endif

    
}

void RenderingSystemUniformBuffer::UpdateLightningData(const GLuint* lights_count)
{
    GLuint* buffer_data =
        (GLuint*)glMapNamedBufferRange(
            uniform_buffer_handle_,
            sizeof(glm::mat4) * 2 + sizeof(glm::vec3) * 2,
            sizeof(glm::vec3),
            GL_WRITE_ONLY
        );

    buffer_data[0] = lights_count[0];
    buffer_data[1] = lights_count[1];
    buffer_data[2] = lights_count[2];

    glUnmapNamedBuffer(uniform_buffer_handle_);
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

    static const GLuint zero_array[] = { 0, 0, 0 };

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
        sizeof(identity_matrix) * 2 + sizeof(zero_vector),
        sizeof(zero_vector),
        glm::value_ptr(zero_vector)
    );

    glNamedBufferSubData(
        uniform_buffer_handle_,
        sizeof(identity_matrix) * 2 + sizeof(zero_vector) * 3,
        sizeof(zero_array),
        zero_array
    );

#endif
}

void RenderingSystemUniformBuffer::DestroyGPUBuffer()
{
    glDeleteBuffers(1, &uniform_buffer_handle_);
}

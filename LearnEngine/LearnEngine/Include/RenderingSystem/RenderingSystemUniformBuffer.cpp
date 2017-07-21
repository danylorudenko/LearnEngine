#include "RenderingSystemUniformBuffer.h"
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtc\matrix_transform.hpp>

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
    glm::vec3& position,
    glm::vec3& rotation,
    GLfloat aspect_ratio,
    GLfloat fow,
    GLfloat near_plane, GLfloat far_plane)
{
    // TODO: add roll support(around z coordinate)
    // Camera view direction calculation ( x = yaw, y = pitch)
    GLfloat short_hypothenuse = std::cosf(glm::radians(rotation.x));
    glm::vec3 direction(
        std::sinf(glm::radians(rotation.y)) * short_hypothenuse,
        std::sinf(glm::radians(rotation.x)),
        std::cosf(glm::radians(rotation.y)) * short_hypothenuse
    );

    glm::mat4 view_matrix = glm::lookAt(position, direction + position, glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 perspective_matrix = glm::perspective(fow, aspect_ratio, near_plane, far_plane);

    GLubyte* buffer_data = (GLubyte*)glMapNamedBuffer(uniform_buffer_handle_, GL_WRITE_ONLY);

    std::memcpy(buffer_data, &view_matrix, sizeof(view_matrix));
    buffer_data += sizeof(view_matrix);

    std::memcpy(buffer_data, &perspective_matrix, sizeof(perspective_matrix));
    buffer_data += sizeof(perspective_matrix);

    std::memcpy(buffer_data, &position, sizeof(position));
    buffer_data += sizeof(position);

    std::memcpy(buffer_data, &rotation, sizeof(rotation));

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

    glCreateBuffers(1, &uniform_buffer_handle_);
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
}

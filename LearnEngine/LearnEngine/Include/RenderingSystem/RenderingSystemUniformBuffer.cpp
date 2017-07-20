#include "RenderingSystemUniformBuffer.h"
#include <glm\gtc\type_ptr.hpp>

RenderingSystemUniformBuffer::RenderingSystemUniformBuffer() :
    uniform_buffer_handle_(0)
{
    AllocateGPUBuffer();
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

    glNamedBufferSubData(
        uniform_buffer_handle_,
        0,
        sizeof(identity_matrix),
        glm::value_ptr(identity_matrix)
    );
    glNamedBufferSubData(
        uniform_buffer_handle_,
        sizeof(decltype(identity_matrix)),
        sizeof(decltype(identity_matrix)),
        glm::value_ptr(identity_matrix)
    );

    glNamedBufferSubData(
        uniform_buffer_handle_,
        sizeof(identity_matrix) + sizeof(identity_matrix),
        sizeof(zero_vector),
        glm::value_ptr(zero_vector)
    );
}

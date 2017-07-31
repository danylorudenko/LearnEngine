#include "..\Include\Component\GLObject\GLTransformation\GLTransform.h"
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

GLTransform::GLTransform()
{
    AllocateGPUBuffer();
    FillGPUBuffer();
}

GLTransform& GLTransform::operator=(const GLTransform& rhs)
{
    glCopyNamedBufferSubData(
        rhs.uniform_buffer_handle_,
        uniform_buffer_handle_,
        0,
        0,
        GPU_BUFFER_SIZE
    );

    position_ = rhs.position_;
    rotation_ = rhs.rotation_;
    scale_ = rhs.scale_;
    
    return *this;
}

void GLTransform::AllocateGPUBuffer()
{
    glCreateBuffers(1, &uniform_buffer_handle_);
    glNamedBufferStorage(uniform_buffer_handle_, GPU_BUFFER_SIZE, nullptr, GL_DYNAMIC_STORAGE_BIT | GL_MAP_READ_BIT | GL_MAP_WRITE_BIT);
}

void GLTransform::FillGPUBuffer()
{
    static const glm::mat4 identity_matrix(
        glm::vec4(1.0f, 0.0f, 0.0f, 0.0f),
        glm::vec4(0.0f, 1.0f, 0.0f, 0.0f),
        glm::vec4(0.0f, 0.0f, 1.0f, 0.0f),
        glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)
    );

    glNamedBufferSubData(uniform_buffer_handle_, 0, GPU_BUFFER_SIZE, glm::value_ptr(identity_matrix));
}

void GLTransform::BindTransformUniformBuffer() const
{
    glBindBufferBase(GL_UNIFORM_BUFFER, TRANSFORM_BLOCK_BINDING_INDEX, uniform_buffer_handle_);
}

void GLTransform::UpdateBuffer()
{
    glm::mat4 identity_matrix(
        glm::vec4(1.0f, 0.0f, 0.0f, 0.0f),
        glm::vec4(0.0f, 1.0f, 0.0f, 0.0f),
        glm::vec4(0.0f, 0.0f, 1.0f, 0.0f),
        glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)
    );

    ApplyScale(&identity_matrix, scale_);
    ApplyRotation(&identity_matrix, rotation_);
    ApplyTranslation(&identity_matrix, position_);

    glNamedBufferSubData(
        uniform_buffer_handle_,
        0,
        sizeof(identity_matrix),
        glm::value_ptr(identity_matrix)
    );
}

inline void GLTransform::ApplyScale(glm::mat4* const source, const glm::vec3& scale)
{
    *source = glm::scale(*source, scale);
}

inline void GLTransform::ApplyRotation(glm::mat4* const source, const glm::vec3& euler)
{
    static const glm::vec3 X_AXIS(1.0f, 0.0f, 0.0f);
    static const glm::vec3 Y_AXIS(0.0f, 1.0f, 0.0f);
    static const glm::vec3 Z_AXIS(0.0f, 0.0f, 1.0f);
    
    *source = glm::rotate(*source, euler.x, X_AXIS);
    *source = glm::rotate(*source, euler.y, Y_AXIS);
    *source = glm::rotate(*source, euler.z, Z_AXIS);
}

inline void GLTransform::ApplyTranslation(glm::mat4* const source, const glm::vec3& position)
{
    *source = glm::translate(*source, position);
}
#include "..\Include\Component\GLObject\GLTransformation\GLTransform.h"
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

GLTransform::GLTransform() : model_mat_outdated_(true)
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

void GLTransform::SetPosition(const glm::vec3 & world_position)
{
    position_ = world_position;
    model_mat_outdated_ = true;
}

void GLTransform::SetPosition(GLfloat x, GLfloat y, GLfloat z)
{
    position_.x = x;
    position_.y = y;
    position_.z = z;

    model_mat_outdated_ = true;
}

void GLTransform::SetPosition(x_type, GLfloat param)
{
    position_.x = param;
    model_mat_outdated_ = true;
}

void GLTransform::SetPosition(y_type, GLfloat param)
{
    position_.y = param;
    model_mat_outdated_ = true;
}

void GLTransform::SetPosition(z_type, GLfloat param)
{
    position_.z = param;
    model_mat_outdated_ = true;
}

void GLTransform::SetRotation(const glm::vec3 & world_rotation_euler)
{
    rotation_ = world_rotation_euler;
    model_mat_outdated_ = true;
}

void GLTransform::SetRotation(GLfloat x, GLfloat y, GLfloat z)
{
    rotation_.x = x;
    rotation_.y = y;
    rotation_.z = z;

    model_mat_outdated_ = true;
}

void GLTransform::SetRotation(x_type, GLfloat param)
{
    rotation_.x = param;
    model_mat_outdated_ = true;
}

void GLTransform::SetRotation(y_type, GLfloat param)
{
    rotation_.y = param;
    model_mat_outdated_ = true;
}

void GLTransform::SetRotation(z_type, GLfloat param)
{
    rotation_.z = param;
    model_mat_outdated_ = true;
}

void GLTransform::SetScale(const glm::vec3 & world_scale)
{
    scale_ = world_scale;
    model_mat_outdated_ = true;
}

void GLTransform::SetScale(GLfloat x, GLfloat y, GLfloat z)
{
    scale_.x = x;
    scale_.y = y;
    scale_.z = z;

    model_mat_outdated_ = true;
}

void GLTransform::SetScale(x_type, GLfloat param)
{
    scale_.x = param;
    model_mat_outdated_ = true;
}

void GLTransform::SetScale(y_type, GLfloat param)
{
    scale_.y = param;
    model_mat_outdated_ = true;
}

void GLTransform::SetScale(z_type, GLfloat param)
{
    scale_.z = param;
    model_mat_outdated_ = true;
}

const glm::vec3 & GLTransform::GetPosition() const
{
    return position_;
}

const glm::vec3 & GLTransform::GetRotation() const
{
    return rotation_;
}

const glm::vec3 & GLTransform::GetScale() const
{
    return scale_;
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

void GLTransform::BindTransformUniformBuffer()
{
    if (model_mat_outdated_) {
        UpdateBuffer();
    }
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

    ApplyTranslation(&identity_matrix, position_);
    ApplyScale(&identity_matrix, scale_);
    ApplyRotation(&identity_matrix, rotation_);

    glNamedBufferSubData(
        uniform_buffer_handle_,
        0,
        sizeof(identity_matrix),
        glm::value_ptr(identity_matrix)
    );

    model_mat_outdated_ = false;
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
    
    *source = glm::rotate(*source, glm::radians(euler.x), X_AXIS);
    *source = glm::rotate(*source, glm::radians(euler.y), Y_AXIS);
    *source = glm::rotate(*source, glm::radians(euler.z), Z_AXIS);
}

inline void GLTransform::ApplyTranslation(glm::mat4* const source, const glm::vec3& position)
{
    *source = glm::translate(*source, position);
}
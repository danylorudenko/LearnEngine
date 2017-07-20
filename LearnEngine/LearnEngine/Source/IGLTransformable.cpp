#include "..\Include\Component\GLObject\GLTransformation\IGLTransformable.h"
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

IGLTransformable::IGLTransformable()
{
    AllocateGPUBuffer();
    FillGPUBuffer();
}

IGLTransformable& IGLTransformable::operator=(const IGLTransformable& rhs)
{
    glCopyNamedBufferSubData(
        rhs.uniform_buffer_handle_,
        uniform_buffer_handle_,
        0,
        0,
        GPU_BUFFER_SIZE
    );
    
    return *this;
}

void IGLTransformable::AllocateGPUBuffer()
{
    glCreateBuffers(1, &uniform_buffer_handle_);
    glNamedBufferStorage(uniform_buffer_handle_, GPU_BUFFER_SIZE, nullptr, GL_DYNAMIC_STORAGE_BIT | GL_MAP_READ_BIT | GL_MAP_WRITE_BIT);
}

void IGLTransformable::FillGPUBuffer()
{
    static const glm::mat4 identity_matrix(
        glm::vec4(1.0f, 0.0f, 0.0f, 0.0f),
        glm::vec4(0.0f, 1.0f, 0.0f, 0.0f),
        glm::vec4(0.0f, 0.0f, 1.0f, 0.0f),
        glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)
    );

    glNamedBufferSubData(uniform_buffer_handle_, 0, GPU_BUFFER_SIZE, glm::value_ptr(identity_matrix));
}

void IGLTransformable::BindTransformUniformBuffer() const
{
    glBindBufferBase(GL_UNIFORM_BUFFER, TRANSFORM_BLOCK_BINDING_INDEX, uniform_buffer_handle_);
}

glm::vec3 IGLTransformable::GetPosition() const
{
    return position_;
}

glm::vec3 IGLTransformable::GetRotation() const
{
    return rotation_;
}

glm::vec3 IGLTransformable::GetScale() const
{
    return scale_;
}

void IGLTransformable::SetPosition(const glm::vec3& new_position)
{
    glm::mat4* buffer_data = (glm::mat4*)glMapNamedBuffer(uniform_buffer_handle_, GL_MAP_READ_BIT | GL_MAP_WRITE_BIT);
    glm::translate(*buffer_data, new_position - position_);
    glUnmapNamedBuffer(uniform_buffer_handle_);

    position_ = new_position;
}

void IGLTransformable::SetPosition(GLfloat x, GLfloat y, GLfloat z)
{
    SetPosition(glm::vec3(x, y, z));
}

void IGLTransformable::SetPosParam(x_type, GLfloat param)
{
    glm::mat4* buffer_data = (glm::mat4*)glMapNamedBuffer(uniform_buffer_handle_, GL_MAP_READ_BIT | GL_MAP_WRITE_BIT);
    glm::translate(*buffer_data, glm::vec3(param, 0.0f, 0.0f));
    glUnmapNamedBuffer(uniform_buffer_handle_);

    position_.x = param;
}

void IGLTransformable::SetPosParam(y_type, GLfloat param)
{
    glm::mat4* buffer_data = (glm::mat4*)glMapNamedBuffer(uniform_buffer_handle_, GL_MAP_READ_BIT | GL_MAP_WRITE_BIT);
    glm::translate(*buffer_data, glm::vec3(0.0f, param, 0.0f));
    glUnmapNamedBuffer(uniform_buffer_handle_);

    position_.y = param;
}

void IGLTransformable::SetPosParam(z_type, GLfloat param)
{
    glm::mat4* buffer_data = (glm::mat4*)glMapNamedBuffer(uniform_buffer_handle_, GL_MAP_READ_BIT | GL_MAP_WRITE_BIT);
    glm::translate(*buffer_data, glm::vec3(0.0f, 0.0f, param));
    glUnmapNamedBuffer(uniform_buffer_handle_);

    position_.z = param;
}

void IGLTransformable::SetRotation(const glm::vec3& new_rotation)
{
    glm::mat4* buffer_data = (glm::mat4*)glMapNamedBuffer(uniform_buffer_handle_, GL_MAP_READ_BIT | GL_MAP_WRITE_BIT);
    
    glm::vec3 rotation_delta = new_rotation - rotation_;

    static const glm::vec3 X_AXIS(1.0f, 0.0f, 0.0f);
    static const glm::vec3 Y_AXIS(0.0f, 1.0f, 0.0f);
    static const glm::vec3 Z_AXIS(0.0f, 0.0f, 1.0f);

    glm::rotate(*buffer_data, glm::radians(rotation_delta.x), X_AXIS);
    glm::rotate(*buffer_data, glm::radians(rotation_delta.y), Y_AXIS);
    glm::rotate(*buffer_data, glm::radians(rotation_delta.z), Z_AXIS);
    glUnmapNamedBuffer(uniform_buffer_handle_);

    rotation_ = new_rotation;
}

void IGLTransformable::SetRotation(GLfloat x, GLfloat y, GLfloat z)
{
    SetRotation(glm::vec3(x, y, z));
}

void IGLTransformable::SetRotParam(x_type, GLfloat param)
{
    glm::mat4* buffer_data = (glm::mat4*)glMapNamedBuffer(uniform_buffer_handle_, GL_MAP_READ_BIT | GL_MAP_WRITE_BIT);

    GLfloat rotation_delta = param - rotation_.x;

    static const glm::vec3 X_AXIS(1.0f, 0.0f, 0.0f);
    glm::rotate(*buffer_data, glm::radians(rotation_delta), X_AXIS);
    glUnmapNamedBuffer(uniform_buffer_handle_);

    rotation_.x = param;
}

void IGLTransformable::SetRotParam(y_type, GLfloat param)
{
    glm::mat4* buffer_data = (glm::mat4*)glMapNamedBuffer(uniform_buffer_handle_, GL_MAP_READ_BIT | GL_MAP_WRITE_BIT);

    GLfloat rotation_delta = param - rotation_.y;

    static const glm::vec3 Y_AXIS(0.0f, 1.0f, 0.0f);
    glm::rotate(*buffer_data, glm::radians(rotation_delta), Y_AXIS);
    glUnmapNamedBuffer(uniform_buffer_handle_);
}

void IGLTransformable::SetRotParam(z_type, GLfloat param)
{
    glm::mat4* buffer_data = (glm::mat4*)glMapNamedBuffer(uniform_buffer_handle_, GL_MAP_READ_BIT | GL_MAP_WRITE_BIT);

    GLfloat rotation_delta = param - rotation_.z;

    static const glm::vec3 Z_AXIS(0.0f, 0.0f, 1.0f);
    glm::rotate(*buffer_data, glm::radians(rotation_delta), Z_AXIS);
    glUnmapNamedBuffer(uniform_buffer_handle_);
}

void IGLTransformable::SetScale(const glm::vec3& new_scale)
{
    glm::mat4* buffer_data = (glm::mat4*)glMapNamedBuffer(uniform_buffer_handle_, GL_MAP_READ_BIT | GL_MAP_WRITE_BIT);
    glm::scale(*buffer_data, new_scale - scale_);
    glUnmapNamedBuffer(uniform_buffer_handle_);

    scale_ = new_scale;
}

void IGLTransformable::SetScale(GLfloat x, GLfloat y, GLfloat z)
{
    SetScale(glm::vec3(x, y, z));
}

void IGLTransformable::SetScaleParam(x_type, GLfloat param)
{
    glm::mat4* buffer_data = (glm::mat4*)glMapNamedBuffer(uniform_buffer_handle_, GL_MAP_READ_BIT | GL_MAP_WRITE_BIT);
    glm::scale(*buffer_data, glm::vec3(param - scale_.x, scale_.y, scale_.z));
    glUnmapNamedBuffer(uniform_buffer_handle_);

    scale_.x = param;
}

void IGLTransformable::SetScaleParam(y_type, GLfloat param)
{
    glm::mat4* buffer_data = (glm::mat4*)glMapNamedBuffer(uniform_buffer_handle_, GL_MAP_READ_BIT | GL_MAP_WRITE_BIT);
    glm::scale(*buffer_data, glm::vec3(scale_.x, param - scale_.y, scale_.z));
    glUnmapNamedBuffer(uniform_buffer_handle_);

    scale_.y = param;
}

void IGLTransformable::SetScaleParam(z_type, GLfloat param)
{
    glm::mat4* buffer_data = (glm::mat4*)glMapNamedBuffer(uniform_buffer_handle_, GL_MAP_READ_BIT | GL_MAP_WRITE_BIT);
    glm::scale(*buffer_data, glm::vec3(scale_.x, scale_.y, param - scale_.z));
    glUnmapNamedBuffer(uniform_buffer_handle_);

    scale_.z = param;
}

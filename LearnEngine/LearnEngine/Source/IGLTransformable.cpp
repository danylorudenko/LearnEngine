#include "..\Include\Component\GLObject\GLTransformation\IGLTransformable.h"
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
    glNamedBufferStorage(uniform_buffer_handle_, GPU_BUFFER_SIZE, nullptr, GL_DYNAMIC_STORAGE_BIT | GL_MAP_READ_BIT);
}

void IGLTransformable::FillGPUBuffer()
{
                               // |   Position      |   Rotation      |   Scale
    const float default_data[] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, };
    glNamedBufferSubData(uniform_buffer_handle_, 0, GPU_BUFFER_SIZE, default_data);
}

void IGLTransformable::BindUniformBuffer()
{
    glBindBufferBase(GL_UNIFORM_BUFFER, TRANSFORM_BLOCK_BINDING_INDEX, uniform_buffer_handle_);
}

glm::vec3 IGLTransformable::GetPosition() const
{
    float* position_data 
        = reinterpret_cast<float*>(
            glMapNamedBufferRange(uniform_buffer_handle_, GPU_POSITION_OFFSET, sizeof(glm::vec3), GL_MAP_READ_BIT)
            );

    glm::vec3 position(position_data[0], position_data[1], position_data[2]);
    glUnmapNamedBuffer(uniform_buffer_handle_);

    return position;
}

glm::vec3 IGLTransformable::GetRotation() const
{
    float* rotation_data
        = reinterpret_cast<float*>(
            glMapNamedBufferRange(uniform_buffer_handle_, GPU_ROTATION_OFFSET, sizeof(glm::vec3), GL_MAP_READ_BIT)
            );

    glm::vec3 rotation(rotation_data[0], rotation_data[1], rotation_data[2]);
    glUnmapNamedBuffer(uniform_buffer_handle_);

    return rotation;
}

glm::vec3 IGLTransformable::GetScale() const
{
    float* scale_data
        = reinterpret_cast<float*>(
            glMapNamedBufferRange(uniform_buffer_handle_, GPU_SCALE_OFFSET, sizeof(glm::vec3), GL_MAP_READ_BIT)
            );

    glm::vec3 scale(scale_data[0], scale_data[1], scale_data[2]);
    glUnmapNamedBuffer(uniform_buffer_handle_);

    return scale;
}

void IGLTransformable::SetPosition(const glm::vec3& world_position)
{
    glNamedBufferSubData(uniform_buffer_handle_, GPU_POSITION_OFFSET, sizeof(glm::vec3), glm::value_ptr(world_position));
}

void IGLTransformable::SetPosition(GLfloat x, GLfloat y, GLfloat z)
{
    SetPosition(glm::vec3(x, y, z));
}

void IGLTransformable::SetPosParam(POS p_name, GLfloat param)
{
    glNamedBufferSubData(uniform_buffer_handle_, GPU_POSITION_OFFSET + static_cast<unsigned int>(p_name), sizeof(GLfloat), &param);
}

void IGLTransformable::SetRotation(const glm::vec3& world_rotation)
{
    glNamedBufferSubData(uniform_buffer_handle_, GPU_ROTATION_OFFSET, sizeof(glm::vec3), glm::value_ptr(world_rotation));
}

void IGLTransformable::SetRotation(GLfloat x, GLfloat y, GLfloat z)
{
    SetRotation(glm::vec3(x, y, z));
}

void IGLTransformable::SetRotParam(ROT p_name, GLfloat param)
{
    glNamedBufferSubData(uniform_buffer_handle_, GPU_ROTATION_OFFSET + static_cast<unsigned int>(p_name), sizeof(GLfloat), &param);
}

void IGLTransformable::SetScale(const glm::vec3& world_scale)
{
    glNamedBufferSubData(uniform_buffer_handle_, GPU_SCALE_OFFSET, sizeof(glm::vec3), glm::value_ptr(world_scale));
}

void IGLTransformable::SetScale(GLfloat x, GLfloat y, GLfloat z)
{
    SetScale(glm::vec3(x, y, z));
}

void IGLTransformable::SetScaleParam(SCALE p_name, GLfloat param)
{
    glNamedBufferSubData(uniform_buffer_handle_, GPU_SCALE_OFFSET + static_cast<unsigned int>(p_name), sizeof(GLfloat), &param);
}

#include "..\Include\Component\GLObject\GLTransformation\ITransformable.h"
#include <glm\gtc\type_ptr.hpp>

ITransformable::ITransformable()
{
    AllocateBuffer();
    FillBuffer();
}

ITransformable& ITransformable::operator=(const ITransformable& rhs)
{
    glCopyNamedBufferSubData(
        rhs.uniform_buffer_handle_,
        uniform_buffer_handle_,
        0,
        0,
        BUFFER_SIZE
    );
}

void ITransformable::AllocateBuffer()
{
    glCreateBuffers(1, &uniform_buffer_handle_);
    glNamedBufferStorage(uniform_buffer_handle_, BUFFER_SIZE, nullptr, GL_DYNAMIC_STORAGE_BIT | GL_MAP_READ_BIT);
}

void ITransformable::FillBuffer()
{
    const float default_data = 0.0f;
    glClearNamedBufferSubData(uniform_buffer_handle_, GL_RGB32F, 0, BUFFER_SIZE, GL_RGB32F, GL_FLOAT, &default_data);
}

void ITransformable::BindUniformBuffer()
{
    glBindBufferBase(GL_UNIFORM_BUFFER, TRANSFORM_BLOCK_BINDING_INDEX, uniform_buffer_handle_);
}

glm::vec3 ITransformable::GetPosition() const
{
    float* position_data 
        = reinterpret_cast<float*>(
            glMapNamedBufferRange(uniform_buffer_handle_, POSITION_OFFSET, sizeof(glm::vec3), GL_MAP_READ_BIT)
            );

    glm::vec3 position(position_data[0], position_data[1], position_data[2]);
    glUnmapNamedBuffer(uniform_buffer_handle_);

    return position;
}

glm::vec3 ITransformable::GetRotation() const
{
    float* rotation_data
        = reinterpret_cast<float*>(
            glMapNamedBufferRange(uniform_buffer_handle_, ROTATION_OFFSET, sizeof(glm::vec3), GL_MAP_READ_BIT)
            );

    glm::vec3 rotation(rotation_data[0], rotation_data[1], rotation_data[2]);
    glUnmapNamedBuffer(uniform_buffer_handle_);

    return rotation;
}

glm::vec3 ITransformable::GetScale() const
{
    float* scale_data
        = reinterpret_cast<float*>(
            glMapNamedBufferRange(uniform_buffer_handle_, SCALE_OFFSET, sizeof(glm::vec3), GL_MAP_READ_BIT)
            );

    glm::vec3 scale(scale_data[0], scale_data[1], scale_data[2]);
    glUnmapNamedBuffer(uniform_buffer_handle_);

    return scale;
}

void ITransformable::SetPosition(glm::vec3& world_position)
{
    glNamedBufferSubData(uniform_buffer_handle_, POSITION_OFFSET, sizeof(world_position), glm::value_ptr(world_position));
}

void ITransformable::SetPosition(float x, float y, float z)
{
    SetPosition(glm::vec3(x, y, z));
}

void ITransformable::SetRotation(glm::vec3& world_rotation)
{
    glNamedBufferSubData(uniform_buffer_handle_, ROTATION_OFFSET, sizeof(world_rotation), glm::value_ptr(world_rotation));
}

void ITransformable::SetRotation(float x, float y, float z)
{
    SetRotation(glm::vec3(x, y, z));
}

void ITransformable::SetScale(glm::vec3& world_scale)
{
    glNamedBufferSubData(uniform_buffer_handle_, SCALE_OFFSET, sizeof(world_scale), glm::value_ptr(world_scale));
}

void ITransformable::SetScale(float x, float y, float z)
{
    SetScale(glm::vec3(x, y, z));
}

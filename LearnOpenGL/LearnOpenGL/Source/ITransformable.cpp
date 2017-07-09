#include "..\Include\Component\GLObject\GLTransformation\ITransformable.h"

void ITransformable::AllocateBuffer()
{
    glCreateBuffers(1, &uniform_buffer_handle_);
    glNamedBufferStorage(uniform_buffer_handle_, BUFFER_SIZE, nullptr, GL_DYNAMIC_STORAGE_BIT);
}

void ITransformable::FillBuffer()
{
    const float default_data = 0.0f;
    glClearNamedBufferSubData(uniform_buffer_handle_, GL_RGB32F, 0, BUFFER_SIZE, GL_R32F, GL_FLOAT, &default_data);
}

void ITransformable::BindUniformBuffer()
{
    glBindBufferBase(GL_UNIFORM_BUFFER, TRANSFORM_BLOCK_BINDING_INDEX, uniform_buffer_handle_);
}

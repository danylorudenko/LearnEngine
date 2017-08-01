#include "..\Include\Component\GLObject\DrawArraysIndirectCommand.h"

DrawArraysIndirectCommand::DrawArraysIndirectCommand() :
    buffer_handle_(0)
{
    Allocate();
}

DrawArraysIndirectCommand::~DrawArraysIndirectCommand()
{
    Deallocate();
}

DrawArraysIndirectCommand::DrawArraysIndirectCommand(const DrawArraysIndirectCommand & rhs) :
     buffer_handle_(0)
{
    glCreateBuffers(1, &buffer_handle_);
    
    void* rhs_data = rhs.MapRead();
    glNamedBufferStorage(
        buffer_handle_,
        BUFFER_SIZE,
        rhs_data,
        GL_DYNAMIC_STORAGE_BIT | GL_MAP_READ_BIT | GL_MAP_WRITE_BIT
    );
    rhs.Unmap();
}

DrawArraysIndirectCommand & DrawArraysIndirectCommand::operator=(const DrawArraysIndirectCommand & rhs)
{
    glCopyNamedBufferSubData(
        rhs.buffer_handle_,
        buffer_handle_,
        0,
        0,
        BUFFER_SIZE
    );

    return *this;
}

DrawArraysIndirectCommand::DrawArraysIndirectCommand(DrawArraysIndirectCommand && rhs) :
    buffer_handle_(rhs.buffer_handle_)
{
    rhs.buffer_handle_ = 0;
}

DrawArraysIndirectCommand & DrawArraysIndirectCommand::operator=(DrawArraysIndirectCommand && rhs)
{
    if (buffer_handle_) {
        glDeleteBuffers(1, &buffer_handle_);
    }
    buffer_handle_ = rhs.buffer_handle_;
    rhs.buffer_handle_ = 0;
    return *this;
}

void DrawArraysIndirectCommand::Allocate()
{
    glCreateBuffers(1, &buffer_handle_);
    glNamedBufferStorage(
        buffer_handle_, 
        BUFFER_SIZE, 
        DEFAULT_DATA, 
        GL_MAP_READ_BIT | GL_MAP_WRITE_BIT | GL_DYNAMIC_STORAGE_BIT
    );
}

void DrawArraysIndirectCommand::Deallocate()
{
    glDeleteBuffers(1, &buffer_handle_);
}

void DrawArraysIndirectCommand::Bind() const
{
    glBindBuffer(GL_DRAW_INDIRECT_BUFFER, buffer_handle_);
}

void DrawArraysIndirectCommand::SetVertexCount(GLuint vertex_count)
{
    glNamedBufferSubData(buffer_handle_, VERTEX_COUNT_OFFSET, sizeof(vertex_count), &vertex_count);
}

void DrawArraysIndirectCommand::SetInstanceCount(GLuint instance_count)
{
    glNamedBufferSubData(buffer_handle_, INSTANCE_COUNT_OFFSET, sizeof(instance_count), &instance_count);
}

void DrawArraysIndirectCommand::SetFirstVertexOffset(GLuint first_vertex_offset)
{
    glNamedBufferSubData(buffer_handle_, FIRST_VERTEX_OFFSET, sizeof(first_vertex_offset), &first_vertex_offset);
}

void DrawArraysIndirectCommand::SetBaseInstance(GLuint base_instance)
{
    glNamedBufferSubData(buffer_handle_, BASE_INSTANCE_OFFSET, sizeof(base_instance), &base_instance);
}

void* DrawArraysIndirectCommand::MapRead() const
{
    return glMapNamedBuffer(buffer_handle_, GL_READ_ONLY);
}

void* DrawArraysIndirectCommand::MapWrite()
{
    return glMapNamedBuffer(buffer_handle_, GL_WRITE_ONLY);
}

void* DrawArraysIndirectCommand::MapReadWrite()
{
    return glMapNamedBuffer(buffer_handle_, GL_READ_WRITE);
}

void DrawArraysIndirectCommand::Unmap() const
{
    glUnmapNamedBuffer(buffer_handle_);
}
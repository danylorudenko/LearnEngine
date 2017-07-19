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

void* DrawArraysIndirectCommand::MapRead() const
{
    return glMapNamedBuffer(buffer_handle_, GL_MAP_READ_BIT);
}

void* DrawArraysIndirectCommand::MapWrite()
{
    return glMapNamedBuffer(buffer_handle_, GL_MAP_WRITE_BIT);
}

void* DrawArraysIndirectCommand::MapReadWrite()
{
    return glMapNamedBuffer(buffer_handle_, GL_MAP_READ_BIT | GL_MAP_WRITE_BIT);
}

void DrawArraysIndirectCommand::Unmap() const
{
    glUnmapNamedBuffer(buffer_handle_);
}
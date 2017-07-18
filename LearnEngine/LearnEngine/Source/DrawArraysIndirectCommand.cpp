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

void DrawArraysIndirectCommand::Allocate()
{
    glCreateBuffers(1, &buffer_handle_);
    glNamedBufferStorage(buffer_handle_, BUFFER_SIZE, DEFAULT_DATA, GL_MAP_READ_BIT | GL_MAP_WRITE_BIT);
}

void DrawArraysIndirectCommand::Deallocate()
{
    glDeleteBuffers(1, &buffer_handle_);
}

void DrawArraysIndirectCommand::Bind() const
{
    glBindBuffer(GL_DRAW_INDIRECT_BUFFER, buffer_handle_);
}

void* DrawArraysIndirectCommand::MapRead()
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

void DrawArraysIndirectCommand::Unmap()
{
    glUnmapNamedBuffer(buffer_handle_);
}
#include "..\Include\Component\GLObject\DrawArraysIndirectCommand.h"
#include "..\Include\Util\Debugging\DebugTools.h"

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

#ifdef GL44

    glBindBuffer(GL_DRAW_INDIRECT_BUFFER, buffer_handle_);
    glBufferStorage(
        GL_DRAW_INDIRECT_BUFFER,
        BUFFER_SIZE,
        rhs_data,
        GL_DYNAMIC_STORAGE_BIT | GL_MAP_READ_BIT | GL_MAP_WRITE_BIT
    );

    display_gl_errors();

#else

    glNamedBufferStorage(
        buffer_handle_,
        BUFFER_SIZE,
        rhs_data,
        GL_DYNAMIC_STORAGE_BIT | GL_MAP_READ_BIT | GL_MAP_WRITE_BIT
    );

#endif

    rhs.Unmap();
}

DrawArraysIndirectCommand & DrawArraysIndirectCommand::operator=(const DrawArraysIndirectCommand & rhs)
{
#ifdef GL44

    glBindBuffer(GL_COPY_READ_BUFFER, rhs.buffer_handle_);
    glBindBuffer(GL_COPY_WRITE_BUFFER, buffer_handle_);
    glCopyBufferSubData(
        GL_COPY_READ_BUFFER,
        GL_COPY_WRITE_BUFFER,
        0,
        0,
        BUFFER_SIZE
    );

    display_gl_errors();

#else

    glCopyNamedBufferSubData(
        rhs.buffer_handle_,
        buffer_handle_,
        0,
        0,
        BUFFER_SIZE
    );

#endif

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

#ifdef GL44

    glBindBuffer(GL_DRAW_INDIRECT_BUFFER, buffer_handle_);
    glBufferStorage(
        GL_DRAW_INDIRECT_BUFFER,
        BUFFER_SIZE,
        DEFAULT_DATA,
        GL_MAP_READ_BIT | GL_MAP_WRITE_BIT | GL_DYNAMIC_STORAGE_BIT
    );

    display_gl_errors();

#else

    glNamedBufferStorage(
        buffer_handle_,
        BUFFER_SIZE,
        DEFAULT_DATA,
        GL_MAP_READ_BIT | GL_MAP_WRITE_BIT | GL_DYNAMIC_STORAGE_BIT
    );

#endif

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
#ifdef GL44

    glBindBuffer(GL_DRAW_INDIRECT_BUFFER, buffer_handle_);
    glBufferSubData(GL_DRAW_INDIRECT_BUFFER, VERTEX_COUNT_OFFSET, sizeof(vertex_count), &vertex_count);

    display_gl_errors();

#else
    
    glNamedBufferSubData(buffer_handle_, VERTEX_COUNT_OFFSET, sizeof(vertex_count), &vertex_count);

#endif
}

void DrawArraysIndirectCommand::SetInstanceCount(GLuint instance_count)
{
#ifdef GL44

    glBindBuffer(GL_DRAW_INDIRECT_BUFFER, buffer_handle_);
    glBufferSubData(GL_DRAW_INDIRECT_BUFFER, INSTANCE_COUNT_OFFSET, sizeof(instance_count), &instance_count);

    display_gl_errors();

#else

    glNamedBufferSubData(buffer_handle_, INSTANCE_COUNT_OFFSET, sizeof(instance_count), &instance_count);

#endif
}

void DrawArraysIndirectCommand::SetFirstVertexOffset(GLuint first_vertex_offset)
{
#ifdef GL44

    glBindBuffer(GL_DRAW_INDIRECT_BUFFER, buffer_handle_);
    glBufferSubData(GL_DRAW_INDIRECT_BUFFER, FIRST_VERTEX_OFFSET, sizeof(first_vertex_offset), &first_vertex_offset);

    display_gl_errors();

#else

    glNamedBufferSubData(buffer_handle_, FIRST_VERTEX_OFFSET, sizeof(first_vertex_offset), &first_vertex_offset);

#endif
}

void DrawArraysIndirectCommand::SetBaseInstance(GLuint base_instance)
{
#ifdef GL44

    glBindBuffer(GL_DRAW_INDIRECT_BUFFER, buffer_handle_);
    glBufferSubData(GL_DRAW_INDIRECT_BUFFER, BASE_INSTANCE_OFFSET, sizeof(base_instance), &base_instance);

    display_gl_errors();

#else

    glNamedBufferSubData(buffer_handle_, BASE_INSTANCE_OFFSET, sizeof(base_instance), &base_instance);

#endif
}

void* DrawArraysIndirectCommand::MapRead() const
{
#ifdef GL44

    glBindBuffer(GL_DRAW_INDIRECT_BUFFER, buffer_handle_);
    return glMapBuffer(GL_DRAW_INDIRECT_BUFFER, GL_READ_ONLY);

#else

    return glMapNamedBuffer(buffer_handle_, GL_READ_ONLY);

#endif
}

void* DrawArraysIndirectCommand::MapWrite()
{
#ifdef GL44

    glBindBuffer(GL_DRAW_INDIRECT_BUFFER, buffer_handle_);
    return glMapBuffer(GL_DRAW_INDIRECT_BUFFER, GL_WRITE_ONLY);

#else

    return glMapNamedBuffer(buffer_handle_, GL_WRITE_ONLY);

#endif
}

void* DrawArraysIndirectCommand::MapReadWrite()
{
#ifdef GL44

    glBindBuffer(GL_DRAW_INDIRECT_BUFFER, buffer_handle_);
    return glMapBuffer(GL_DRAW_INDIRECT_BUFFER, GL_READ_WRITE);

#else

    return glMapNamedBuffer(buffer_handle_, GL_READ_WRITE);

#endif
}

void DrawArraysIndirectCommand::Unmap() const
{
#ifdef GL44

    glBindBuffer(GL_DRAW_INDIRECT_BUFFER, buffer_handle_);
    glUnmapBuffer(GL_DRAW_INDIRECT_BUFFER);

#else

    glUnmapNamedBuffer(buffer_handle_);

#endif
}
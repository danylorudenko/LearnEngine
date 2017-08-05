#include "..\Include\VertexData\VertexData.h"
#include "..\Include\Util\Debugging\DebugTools.h"

#include <cstdlib>

VertexData::VertexData(void* data, GLuint vertex_count, GLsizei size, GLsizei stride, GLuint offset) : 
    vertex_data_(data), 
    data_size_(size),
    stride_(stride),
    vertex_count_(vertex_count),
    vertex_data_offset_(offset),
    vertex_buffer_object_(0),
    vertex_array_object_(0)
{
    CreateAndFillVertexBuffer();
    CreateVAO();
}

VertexData::~VertexData()
{
    DeleteVertexBuffer();
    DeleteVAO();
    std::free(vertex_data_);
}

void VertexData::CreateVAO()
{
    glCreateVertexArrays(1, &vertex_array_object_);
}

void VertexData::DeleteVAO()
{
    glDeleteVertexArrays(1, &vertex_array_object_);
}

void VertexData::CreateAndFillVertexBuffer()
{
    glCreateBuffers(1, &vertex_buffer_object_);

#ifdef GL44

    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object_);
    glBufferStorage(GL_ARRAY_BUFFER, RawDataSize(), RawData(), 0);

    display_gl_errors();

#else

    glNamedBufferStorage(vertex_buffer_object_, RawDataSize(), RawData(), 0);

#endif
}

void VertexData::DeleteVertexBuffer()
{
    glDeleteBuffers(1, &vertex_buffer_object_);
}

void VertexData::SetDrawCommand(const DrawArraysIndirectCommand & command)
{
    draw_arrays_command_ = command;
}

void VertexData::SetDrawCommand(DrawArraysIndirectCommand && command)
{
    draw_arrays_command_ = std::move(command);
}

void VertexData::Bind() const
{
    BindVAO();
    BindDrawCommand();
}

void VertexData::BindDrawCommand() const
{
    draw_arrays_command_.Bind();
}

void VertexData::BindVAO() const
{
    glBindVertexArray(vertex_array_object_);
}

void VertexData::AddVAOVertexAttrib(const VertexAttribData& data)
{
#ifdef GL44

    glBindVertexArray(vertex_array_object_);
    
    glVertexAttribFormat(
        data.attrib_index_,
        data.element_count_,
        data.attrib_gl_format_,
        data.normalized_,
        data.offset_
    );

    display_gl_errors();

    glBindVertexBuffer(
        data.binding_index_,
        vertex_buffer_object_,
        vertex_data_offset_,
        stride_
    );

    display_gl_errors();

    glVertexAttribBinding(
        data.attrib_index_,
        data.binding_index_
    );

    display_gl_errors();

    glEnableVertexAttribArray(
        data.attrib_index_
    );

    display_gl_errors();


#else

    glVertexArrayAttribFormat(
        vertex_array_object_,
        data.attrib_index_,
        data.element_count_,
        data.attrib_gl_format_,
        data.normalized_,
        data.offset_
        );

    display_gl_errors();

    glVertexArrayVertexBuffer(
        vertex_array_object_,
        data.binding_index_,
        vertex_buffer_object_,
        vertex_data_offset_,
        stride_
    );

    display_gl_errors();

    glVertexArrayAttribBinding(
        vertex_array_object_,
        data.attrib_index_,
        data.binding_index_
    );

    display_gl_errors();

    glEnableVertexArrayAttrib(
        vertex_array_object_,
        data.attrib_index_
    );

    display_gl_errors();

#endif
}

GLsizei VertexData::RawDataSize() const
{
    return data_size_;
}

void * VertexData::RawData() const
{
    return vertex_data_;
}

GLuint VertexData::VertexCount() const
{
    return vertex_count_;
}

GLuint VertexData::Offset() const
{
    return vertex_data_offset_;
}

GLsizei VertexData::Stride() const
{
    return stride_;
}

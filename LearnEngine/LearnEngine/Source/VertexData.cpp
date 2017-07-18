#include "..\Include\VertexData\VertexData.h"

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

VertexData::VertexData(VertexData && rhs) : 
    vertex_data_(rhs.vertex_data_),
    data_size_(rhs.data_size_), 
    stride_(rhs.stride_),
    vertex_count_(rhs.vertex_count_),
    vertex_data_offset_(rhs.vertex_data_offset_),
    vertex_buffer_object_(rhs.vertex_buffer_object_),
    vertex_array_object_(rhs.vertex_array_object_)
{
    vertex_array_object_ = 0;
    rhs.data_size_ = 0;
    rhs.vertex_data_ = nullptr;
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
    glNamedBufferStorage(vertex_buffer_object_, data_size_, vertex_data_, 0);
}

void VertexData::DeleteVertexBuffer()
{
    glDeleteBuffers(1, &vertex_buffer_object_);
}

void VertexData::BindVAO() const
{
    glBindVertexArray(vertex_array_object_);
}

void VertexData::AddVAOVertexAttrib(const VertexAttribData& data)
{
    // NEED REFERENCE ABOUT ALL THAT BINDING INDICIES STUFF
    asdiuyethaiewljofgy

    glVertexArrayAttribFormat(
        vertex_array_object_,
        data.attrib_index_,
        data.attrib_size_,
        data.attrib_gl_format_,
        data.normalized_,
        data.offset_
        );

    glVertexArrayAttribBinding(
        vertex_array_object_,
        data.attrib_index_,
        data.binding_index_
    );

    glVertexArrayVertexBuffer(
        vertex_array_object_,
        data.binding_index_,
        vertex_buffer_object_,
        0,
        stride_
    );

    glEnableVertexArrayAttrib(
        vertex_array_object_,
        data.attrib_index_
    );
}

GLsizei VertexData::DataRawSize() const
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

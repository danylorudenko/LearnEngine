#include "..\Include\VertexData\VertexData.h"

#include <cstdlib>

VertexData::VertexData(void* data, GLuint vertex_count, GLsizei size, GLuint offset) : 
    vertex_data_(data), 
    vertex_count_(vertex_count),
    data_size_(size),
    vertex_data_offset_(offset),
    stride_(0)
{
    
}

VertexData::VertexData(const VertexData & rhs) : 
    data_size_(rhs.data_size_),
    vertex_attributes_(rhs.vertex_attributes_),
    vertex_count_(rhs.vertex_count_),
    vertex_data_offset_(rhs.vertex_data_offset_),
    stride_(rhs.stride_)
{
    vertex_data_ = std::malloc(data_size_);

    // Copying of all bytes to the newly allocated memory.
    // Pointer arythmetic can't be done with void*, so casting to char* is necessary.
    std::memcpy(vertex_data_, rhs.vertex_data_, data_size_);
}

VertexData::VertexData(VertexData && rhs) : 
    data_size_(rhs.data_size_), 
    vertex_data_(rhs.vertex_data_),
    vertex_count_(rhs.vertex_count_),
    vertex_data_offset_(rhs.vertex_data_offset_),
    vertex_attributes_(std::move(vertex_attributes_)),
    stride_(rhs.stride_)
{
    rhs.data_size_ = 0;
    rhs.vertex_data_ = nullptr;
    rhs.ClearAttribData();
}

VertexData::~VertexData()
{
    std::free(vertex_data_);
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

const VertexData::VertexAttribDataContainer& VertexData::AttribDataCollection() const
{
    return vertex_attributes_;
}

void VertexData::ClearAttribData()
{
    vertex_attributes_.clear();

}

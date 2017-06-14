#include "..\Include\VertexData.h"

#include <cstdlib>

VertexData::VertexData(void * data, int size)
{
    vertex_data_ = data;
    data_size_ = size;
}

VertexData::VertexData(const VertexData & rhs)
{
    data_size_ = rhs.data_size_;

    vertex_data_ = std::malloc(data_size_);

    // Copying of all bytes to the newly allocated memory.
    // Pointer arythmetic can't be done with void*, so casting to char* is necessary.
    for (int i = 0; i < data_size_; i++) {
        *(reinterpret_cast<char*>(vertex_data_) + i) = *(reinterpret_cast<char*>(rhs.vertex_data_) + i);
    }
}

VertexData::VertexData(VertexData && rhs)
{
    data_size_ = rhs.data_size_;
    rhs.data_size_ = 0;

    vertex_data_ = rhs.vertex_data_;
    rhs.vertex_data_ = nullptr;
}

VertexData::~VertexData()
{
    std::free(vertex_data_);
}

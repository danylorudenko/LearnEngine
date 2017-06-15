#ifndef __VERTEX_DATA_H__
#define __VERTEX_DATA_H__

class VertexData
{
public:
    VertexData                              (void* data, int size);

    int                  GetDataSize        ();
    void*                GetRawData         ();

    VertexData                              (const VertexData& rhs);
    VertexData&          operator=          (const VertexData& rhs) = delete;

    VertexData                              (VertexData&& rhs);
    VertexData&          operator=          (VertexData&& rhs) = delete;

    ~VertexData                             ();

private:
    void* vertex_data_;
    int data_size_;
};

#endif
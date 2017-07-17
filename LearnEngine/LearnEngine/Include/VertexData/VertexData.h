#ifndef __VERTEX_DATA_H__
#define __VERTEX_DATA_H__

#include <vector>

#include <gl\glew.h>
#include "VertexAttribData.h"

class VertexData
{
public:
    using VertexAttribDataContainer = std::vector<VertexAttribData>;

    VertexData                                              (void* data, GLuint vertex_count, GLsizei size, GLuint offset);

    VertexData                                              (const VertexData& rhs);
    VertexData&                         operator=           (const VertexData& rhs) = delete;

    VertexData(VertexData&& rhs);
    VertexData&                         operator=           (VertexData&& rhs) = delete;

    // ================ General info ==================

    // Size of internal data array in bytes.
    GLsizei                             DataRawSize         () const;

    void*                               RawData             () const;
    GLuint                              VertexCount         () const;

    // Offset of the vertex data in the internal array.
    GLuint                              Offset              () const; 

    // Stride between vertices in the internal array.
    GLsizei                             Stride              () const;



    // ================ Attributes data manipulation ===================
    
    // Const getter for internal attributes data container.
    const VertexAttribDataContainer&    AttribDataCollection() const;

    // Clearing internal attributes data containter.
    // Sets stride to 0.
    void                                ClearAttribData     ();
    
    // Copying or moving new attribute data to the internal container.
    // Automatically adjusts stride of the vertex.
    template<typename TAttrib>
    void                                AddAttribData       (TAttrib&& data)
    {
        vertex_attributes_.push_back(std::forward(data));
    }

    // Constructs attribute at the end of attribute info list.
    // Automatically adjusts stride of the vertex.
    // Argiuments: (GLenum attrib_gl_format, GLuint offset, GLubyte attrib_size_, GLubyte element_count)
    template<
        typename TAttrib, 
        typename... TAttribArgs
    >
    void                                EmplaceAttribData   (TAttribArgs... args)
    {
        vertex_attributes_.emplace_back(args...);
    }

    virtual ~VertexData                                     ();

protected:
    void*                                                   vertex_data_;
    GLsizei                                                 data_size_;
    GLsizei                                                 stride_;
    GLuint                                                  vertex_count_;
    GLuint                                                  vertex_data_offset_;
    
    GLuint                                                  vertex_array_object_;
    VertexAttribDataContainer                               vertex_attributes_;
};

#endif
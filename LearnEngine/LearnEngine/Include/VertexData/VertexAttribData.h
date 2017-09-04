#ifndef __VERTEX_ATTRIB_DATA_H__
#define __VERTEX_ATTRIB_DATA_H__

#include <gl\glew.h>

// Aggregator of data needed to describe vertex attribute to OpenGL.
class VertexAttribData
{
public:
    VertexAttribData                                        (GLuint attrib_index,
                                                             GLuint binding_index,
                                                             GLenum attrib_gl_format, 
                                                             GLuint offset, 
                                                             GLboolean normalized,
                                                             GLubyte attrib_size_, 
                                                             GLubyte element_count);

    VertexAttribData                                        (const VertexAttribData& rhs) = default;
    VertexAttribData                                        (VertexAttribData&& rhs) = default;

    VertexAttribData&               operator=               (const VertexAttribData& rhs) = default;
    VertexAttribData&               operator=               (VertexAttribData&& rhs) = default;

    GLuint                          attrib_index_;
    GLuint                          binding_index_;                      
    GLenum                          attrib_gl_format_;
    GLuint                          offset_;
    GLboolean                       normalized_;
    GLubyte                         attrib_size_;
    GLubyte                         element_count_;
};

#endif
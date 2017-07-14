#ifndef __VERTEX_ATTRIB_DATA_H__
#define __VERTEX_ATTRIB_DATA_H__

#include <gl\glew.h>

class VertexAttribData
{
public:
    VertexAttribData                                        (GLenum attrib_gl_format, GLuint offset, GLubyte attrib_size_, GLubyte element_count);
    VertexAttribData                                        (const VertexAttribData& rhs) = default;
    VertexAttribData                                        (VertexAttribData&& rhs) = default;

    VertexAttribData&               operator=               (const VertexAttribData& rhs) = default;
    VertexAttribData&               operator=               (VertexAttribData&& rhs) = default;

    GLenum                          attrib_gl_format_;
    GLuint                          offset_;
    GLubyte                         attrib_size_;
    GLubyte                         element_count_;
    
};

#endif
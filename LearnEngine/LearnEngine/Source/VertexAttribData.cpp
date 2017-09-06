#include <Engine\VertexData\VertexAttribData.h>

VertexAttribData::VertexAttribData(
    GLuint attrib_index,
    GLuint binding_index,
    GLenum attrib_gl_format, 
    GLuint offset, 
    GLboolean normalized,
    GLubyte attrib_size, 
    GLubyte element_count) :
    attrib_index_(attrib_index),
    binding_index_(binding_index),
    attrib_gl_format_(attrib_gl_format),
    offset_(offset),
    normalized_(normalized),
    attrib_size_(attrib_size),
    element_count_(element_count)
{

}
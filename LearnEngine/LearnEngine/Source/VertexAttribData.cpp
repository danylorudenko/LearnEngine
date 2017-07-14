#include "..\Include\VertexData\VertexAttribData.h"

VertexAttribData::VertexAttribData(GLenum attrib_gl_format, GLuint offset, GLubyte attrib_size, GLubyte element_count) :
    attrib_gl_format_(attrib_gl_format),
    offset_(offset),
    attrib_size_(attrib_size),
    element_count_(element_count)
{

}
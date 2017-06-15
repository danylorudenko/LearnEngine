#include "..\Include\GLObject\GLObject.h"

GLObject::GLObject(std::shared_ptr<VertexData> vertex_data, std::shared_ptr<ShaderProgram> shader_program) :
    vertex_data_(vertex_data), main_shader_program_(shader_program)
{

}

GLObject::~GLObject()
{

}

GLObject::GLObject(GLObject && rhs) : 
    vertex_data_(rhs.vertex_data_), main_shader_program_(rhs.main_shader_program_)
{
    
}

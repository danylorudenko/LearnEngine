#include <glm\vec3.hpp>
#include <glm\mat4x4.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include "..\Include\Component\GLObject\GLObject.h"

GLObject::GLObject(std::shared_ptr<VertexData> vertex_data, std::shared_ptr<Material> main_material) :
    Component(),
    vertex_data_    (vertex_data), 
    main_material_  (main_material),
    transfrom_data_(nullptr)
{
    
}

GLObject::GLObject(const GLObject& rhs) : 
    Component(rhs),
    vertex_data_    (rhs.vertex_data_), 
    main_material_  (rhs.main_material_),
    transfrom_data_(nullptr)
{
    
}

GLObject& GLObject::operator=(const GLObject& rhs)
{
    Component::operator=(rhs);
}

GLObject::GLObject(GLObject&& rhs) :
    Component(std::move(rhs))
{

}

GLObject& GLObject::operator=(GLObject&& rhs)
{
    Component::operator=(std::move(rhs));
}

GLObject::~GLObject()
{

}

void GLObject::AllocateTransformStorage()
{
    transfrom_data_ = new GLfloat[TRANSFORM_BUFFER_SIZE];
}

void GLObject::SetTransfromDefaults()
{
                               // |   Position      |   Rotation      |   Scale
    const GLfloat default_data[] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, };
    std::memcpy(transfrom_data_, default_data, TRANSFORM_BUFFER_SIZE);
}

Material& GLObject::GetMainMaterial()
{
    return *main_material_;
}
//
//glm::mat4 GLObject::GetModelMatrix() const
//{
//    glm::mat4 model_matrix;
//    model_matrix = glm::scale(model_matrix, *world_scale_);
//
//    // Rotate around every axis.
//    model_matrix = glm::rotate(model_matrix, glm::radians(world_euler_->x), glm::vec3(1.0f, 0.0f, 0.0f));
//    model_matrix = glm::rotate(model_matrix, glm::radians(world_euler_->y), glm::vec3(0.0f, 1.0f, 0.0f));
//    model_matrix = glm::rotate(model_matrix, glm::radians(world_euler_->z), glm::vec3(0.0f, 0.0f, 1.0f));
//
//    model_matrix = glm::translate(model_matrix, *world_position_);
//
//    return model_matrix;
//}

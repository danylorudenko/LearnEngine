#include <glm\mat4x4.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include "..\Include\Component\GLObject\GLObject.h"
#include "..\Include\RenderingSystem\RenderingSystem.h"
#include "..\Include\Util\CustomException\not_implemented_exc.h"

GLObject::GLObject(std::shared_ptr<VertexData> vertex_data, std::shared_ptr<Material> main_material) :
    Component(),
    vertex_data_    (vertex_data), 
    main_material_  (main_material)
{
    
}

GLObject::GLObject(const GLObject& rhs) : 
    Component(rhs),
    vertex_data_    (rhs.vertex_data_), 
    main_material_  (rhs.main_material_)
{
    
}

GLObject& GLObject::operator=(const GLObject& rhs)
{
    Component::operator=(rhs);
    
    return *this;
}

GLObject::GLObject(GLObject&& rhs) :
    Component(std::move(rhs))
{

}

GLObject& GLObject::operator=(GLObject&& rhs)
{
    Component::operator=(std::move(rhs));

    return *this;
}

GLObject::~GLObject()
{

}

void GLObject::RegisterInSystem()
{
    RenderingSystem::Instance().AddToDrawList(this);
}

void GLObject::UnregisterFromSystem()
{
    RenderingSystem::Instance().RemoveFromDrawList(this);
}

Material& GLObject::GetMainMaterial()
{
    return *main_material_;
}

void GLObject::BindStandardUnifromBlocks()
{
    throw not_implemented_exc("GLObject::BindStandardUniformBlocks was not implemented.");
}

std::tuple<GLuint, GLuint> GLObject::GetDrawRange()
{
    // Not sure if it is right.
    return std::tuple<GLuint, GLuint>(0, vertex_data_->VertexCount());
}

void GLObject::SetVertexData(std::shared_ptr<VertexData>& vertex_data)
{
    vertex_data_ = vertex_data;
}

void GLObject::BindToRender() const
{
    throw not_implemented_exc("GLOjbect::BindToRender was not implemented.");
}

std::shared_ptr<Material> GLObject::GetMainMaterialShared()
{
    return main_material_;
}

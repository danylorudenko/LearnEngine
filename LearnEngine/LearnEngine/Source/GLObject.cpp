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

void GLObject::SetVertexData(std::shared_ptr<VertexData>& vertex_data)
{
    vertex_data_ = vertex_data;

    void* indirect_buffer = draw_arrays_command_.MapWrite();

    *((GLuint*)indirect_buffer + DrawArraysIndirectCommand::VERTEX_COUNT_OFFSET) = vertex_data_->VertexCount();
}

void GLObject::BindToRender() const
{
    throw not_implemented_exc("GLOjbect::BindToRender was not implemented.");

    main_material_->GetShader().Use();
    main_material_->BindAllTextures();

    sakhgacjlwemcgfnuk
}

std::shared_ptr<Material> GLObject::GetMainMaterialShared()
{
    return main_material_;
}

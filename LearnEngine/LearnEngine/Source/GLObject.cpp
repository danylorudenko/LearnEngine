#include "..\Include\Component\GLObject\GLObject.h"
#include "..\Include\Entity\Entity.h"
#include "..\Include\RenderingSystem\RenderingSystem.h"

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
    RenderingSystem::Instance().AddToRenderingList(this);
}

void GLObject::UnregisterFromSystem()
{
    RenderingSystem::Instance().RemoveFromRenderingList(this);
}

Material& GLObject::GetMainMaterial()
{
    return *main_material_;
}

void GLObject::BindStandardUnifromBlocks()
{
    owner_->Transform().BindTransformUniformBuffer();
}

void GLObject::SetVertexData(const std::shared_ptr<VertexData>& vertex_data)
{
    vertex_data_ = vertex_data;
}

void GLObject::BindToRender()
{
    main_material_->GetShader().Use();
    main_material_->BindAllTextures();

    BindStandardUnifromBlocks();

    vertex_data_->Bind();
}

std::shared_ptr<Material> GLObject::GetMainMaterialShared()
{
    return main_material_;
}

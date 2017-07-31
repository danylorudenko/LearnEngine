#include <glm\mat4x4.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include "..\Include\Component\GLObject\GLObject.h"
#include "..\Include\RenderingSystem\RenderingSystem.h"
#include "..\Include\Util\CustomException\not_implemented_exc.h"

GLObject::GLObject(std::shared_ptr<VertexData> vertex_data, std::shared_ptr<Material> main_material) :
    Component(),
    GLTransform(),
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

void GLObject::BindStandardUnifromBlocks() const
{
    GLTransform::BindTransformUniformBuffer();
}

void GLObject::SetVertexData(std::shared_ptr<VertexData>& vertex_data)
{
    vertex_data_ = vertex_data;
}

void GLObject::BindToRender() const
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

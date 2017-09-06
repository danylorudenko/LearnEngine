#include <Engine\Component\GLObject\GLObject.h>
#include <Engine\Entity\Entity.h>
#include <Engine\RenderingSystem\RenderingSystem.h>
#include <Engine\Component\ComponentFactory.h>

GLObject::GLObject() :
    Component()
{
    
}

Component::DestructionFunction GLObject::GetDestructionFunc()
{
    return [](Component* this_component) 
    { 
        ComponentFactory<GLObject>::DestroyComponent(dynamic_cast<GLObject*>(this_component)); 
    };
}

GLObject::~GLObject()
{

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

void GLObject::SetMainMaterial(const std::shared_ptr<Material>& material)
{
    main_material_ = material;
}

std::shared_ptr<Material> GLObject::GetMainMaterialShared()
{
    return main_material_;
}

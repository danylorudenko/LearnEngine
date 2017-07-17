#include "..\Include\Material\Material.h"
#include <glm\mat4x4.hpp>

Material::Material(std::shared_ptr<ShaderProgram> shader) : main_shader_(shader)
{

}

Material::Material(const Material& rhs) :
    main_shader_(rhs.main_shader_),
    main_texture_(rhs.main_texture_)
{

}

Material::~Material()
{

}

void Material::SetMainShader(std::shared_ptr<ShaderProgram> shader)
{
    main_shader_ = shader;
}

ShaderProgram& Material::GetMainShader()
{
    return *main_shader_;
}

TextureController& Material::GetMainTexture()
{
    return *main_texture_;
}

void Material::Bind()
{
    GetMainShader().Use();
    GetMainTexture().Bind();

    GetMainShader().SetSampler("myTexture1", 0);
}

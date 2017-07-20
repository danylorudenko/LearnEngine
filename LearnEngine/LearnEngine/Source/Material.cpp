#include "..\Include\Material\Material.h"
#include <glm\mat4x4.hpp>

Material::Material(std::shared_ptr<ShaderProgram> shader) : main_shader_(shader)
{

}

Material::Material(const Material& rhs) :
    main_shader_(rhs.main_shader_)
{

}

Material& Material::operator=(const Material& rhs)
{
    main_shader_ = rhs.main_shader_;
    return *this;
}

Material::~Material()
{

}

void Material::SetShader(std::shared_ptr<ShaderProgram>& shader)
{
    main_shader_ = shader;
}

ShaderProgram& Material::GetShader()
{
    return *main_shader_;
}

void Material::AddTexture(GLuint unit, std::shared_ptr<TextureController>& texture)
{
    textures_.push_back(UnitTexturePair(unit, texture));
}

std::shared_ptr<ShaderProgram> Material::GetShaderShared()
{
    return main_shader_;
}

void Material::BindAllTextures()
{
    int size = static_cast<int>(textures_.size());
    for (int i = 0; i < size; i++)
    {
        std::get<1>(textures_[i])->BindAllToUnit(std::get<0>(textures_[i]));
    }
}

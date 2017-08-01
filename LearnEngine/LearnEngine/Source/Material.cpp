#include "..\Include\Material\Material.h"
#include <glm\mat4x4.hpp>
#include <algorithm>

Material::Material(std::shared_ptr<ShaderProgram> shader) : main_shader_(shader)
{

}

Material::Material(const Material& rhs) :
    main_shader_(rhs.main_shader_),
    textures_(rhs.textures_)
{

}

Material& Material::operator=(const Material& rhs)
{
    main_shader_ = rhs.main_shader_;
    textures_ = rhs.textures_;
    return *this;
}

Material::~Material()
{

}

void Material::SetShader(const std::shared_ptr<ShaderProgram>& shader)
{
    main_shader_ = shader;
}

ShaderProgram& Material::GetShader()
{
    return *main_shader_;
}

void Material::AddTexture(GLuint unit, const std::shared_ptr<TextureController>& texture)
{
    RemoveTexture(unit);
    textures_.push_back(UnitTexturePair(unit, texture));
}

void Material::RemoveTexture(GLuint unit)
{
    std::remove_if(textures_.begin(), textures_.end(), 
        [unit](const UnitTexturePair& pair_candidate) {
            return unit == std::get<0>(pair_candidate);
    });
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

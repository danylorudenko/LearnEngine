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

void Material::SetMainTexture(std::shared_ptr<TextureController> texture)
{
    main_texture_ = texture;
}

ShaderProgram& Material::GetMainShader()
{
    return *main_shader_;
}

TextureController& Material::GetMainTexture()
{
    return *main_texture_;
}

void Material::SendTransformData(glm::mat4& model_matrix,
                                 glm::mat4& view_matrix,
                                 glm::mat4& perspective_matrix)
{
    main_shader_->SetMatrix4Uniform(ShaderProgram::MODEL_MATRIX_NAME, model_matrix);
    main_shader_->SetMatrix4Uniform(ShaderProgram::VIEW_MATRIX_NAME, view_matrix);
    main_shader_->SetMatrix4Uniform(ShaderProgram::PERSPECTIVE_MATRIX_NAME, perspective_matrix);
}

void Material::PrepareToDraw()
{
    GetMainShader().Use();
    GetMainTexture().Bind();

    GetMainShader().SetSampler("myTexture1", 0);
}

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

std::shared_ptr<ShaderProgram> Material::GetMainShader()
{
    return main_shader_;
}

void Material::UseMainShader()
{
    main_shader_->Use();
}

void Material::SendTransformData(std::shared_ptr<Camera> camera, glm::mat4& model_matrix, int viewport_width, int viewport_height)
{
    main_shader_->SetMatrix4Uniform(ShaderProgram::MODEL_MATRIX_NAME, model_matrix);
    main_shader_->SetMatrix4Uniform(ShaderProgram::VIEW_MATRIX_NAME, camera->GetViewMatrix());
    main_shader_->SetMatrix4Uniform(ShaderProgram::PERSPECTIVE_MATRIX_NAME, camera->GetPerspectiveMatrix(viewport_width, viewport_height));
}
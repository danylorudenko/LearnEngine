#include <glm\vec3.hpp>
#include <glm\mat4x4.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include "..\Include\RenderingSystem\GLObject\GLObject.h"

GLObject::GLObject(std::shared_ptr<VertexData> vertex_data, std::shared_ptr<ShaderProgram> shader_program) :
    vertex_data_(vertex_data), 
    main_shader_program_(shader_program),
    world_position_(new glm::vec3(0.0f)),
    world_euler_(new glm::vec3(0.0f)),
    world_scale_(new glm::vec3(0.0f))
{

}

GLObject::~GLObject()
{

}

GLObject::GLObject(GLObject && rhs) : 
    vertex_data_(rhs.vertex_data_), 
    main_shader_program_(rhs.main_shader_program_),
    world_position_(rhs.world_position_),
    world_euler_(rhs.world_euler_),
    world_scale_(rhs.world_scale_)
{
    rhs.world_position_ = nullptr;
    rhs.world_euler_ = nullptr;
    rhs.world_scale_ = nullptr;
}

void GLObject::SetWorldPosition(const glm::vec3 & position)
{
    *world_position_ = position;
}

void GLObject::SetWorldRotation(const glm::vec3 & euler_angles)
{
    *world_euler_ = euler_angles;
}

void GLObject::SetWorldScale(const glm::vec3 & scale)
{
    *world_scale_ = scale;
}

void GLObject::UseShader_SendTransfromData(std::shared_ptr<Camera> camera, int viewport_width, int viewport_height)
{
    main_shader_program_->Use();

    main_shader_program_->SetMatrix4Uniform(ShaderProgram::MODEL_MATRIX_NAME, this->GetModelMatrix());
    main_shader_program_->SetMatrix4Uniform(ShaderProgram::VIEW_MATRIX_NAME, camera->GetViewMatrix());
    main_shader_program_->SetMatrix4Uniform(ShaderProgram::PERSPECTIVE_MATRIX_NAME, camera->GetPerspectiveMatrix(viewport_width, viewport_height));
}


glm::mat4 GLObject::GetModelMatrix()
{
    glm::mat4 model_matrix;
    model_matrix = glm::scale(model_matrix, *world_scale_);

    // Rotate around every axis.
    model_matrix = glm::rotate(model_matrix, glm::radians(world_euler_->x), glm::vec3(1.0f, 0.0f, 0.0f));
    model_matrix = glm::rotate(model_matrix, glm::radians(world_euler_->y), glm::vec3(0.0f, 1.0f, 0.0f));
    model_matrix = glm::rotate(model_matrix, glm::radians(world_euler_->z), glm::vec3(0.0f, 0.0f, 1.0f));

    model_matrix = glm::translate(model_matrix, *world_position_);

    return model_matrix;
}

void GLObject::SetMainShader(std::shared_ptr<ShaderProgram> shader)
{
    main_shader_program_ = shader;
}

void GLObject::SetMainTexture(std::shared_ptr<DoubleTextureController> texture)
{
    main_texture_ = texture;
}

#include <iostream>
#include <glm\vec3.hpp>
#include <glm\matrix.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include "..\Include\GLObject\GLTestCube.h"

GLTestCube::GLTestCube(std::shared_ptr<VertexData> vertex_data, std::shared_ptr<ShaderProgram> shader_program) :
    GLObject(vertex_data, shader_program), 
    world_position_(new glm::vec3(0.0f)), 
    world_euler_(new glm::vec3(0.0f)), 
    world_scale_(new glm::vec3(0.0f))
{

}

GLTestCube::~GLTestCube()
{
    delete world_position_;
    delete world_euler_;
    delete world_scale_;
}

void GLTestCube::SetWorldPosition(const glm::vec3 & position)
{
    *world_position_ = position;
}

void GLTestCube::SetWorldRotation(const glm::vec3 & euler_angles)
{
    *world_euler_ = euler_angles;
}

void GLTestCube::SetWorldScale(const glm::vec3 & scale)
{
    *world_scale_ = scale;
}


glm::mat4 GLTestCube::GetModelMatrix()
{
    glm::mat4 model_matrix;
    model_matrix = glm::scale(model_matrix, *world_scale_);

    // Rotate around every axis.
    model_matrix = glm::rotate(model_matrix, glm::radians((*world_euler_).x), glm::vec3(1.0f, 0.0f, 0.0f));
    model_matrix = glm::rotate(model_matrix, glm::radians((*world_euler_).y), glm::vec3(0.0f, 1.0f, 0.0f));
    model_matrix = glm::rotate(model_matrix, glm::radians((*world_euler_).z), glm::vec3(0.0f, 0.0f, 1.0f));

    model_matrix = glm::translate(model_matrix, *world_position_);

    return model_matrix;
}

glm::mat4 GLTestCube::GetViewMatrix(const glm::vec3& camera_pos, const glm::vec3& camera_dir)
{
    return glm::lookAt(camera_pos, camera_dir, glm::vec3(0.0f, 1.0f, 0.0f));
}

glm::mat4 GLTestCube::GetProjMatrix(const GLfloat aspect_ratio, const GLfloat fow)
{
    return glm::perspective(fow, aspect_ratio, 0.1f, 100.0f);
}

void GLTestCube::LoadVertexData(std::shared_ptr<VertexData> vertex_data, std::shared_ptr<VertexData> indicies)
{
    glGenBuffers(1, &vertex_array_object_);
    glGenBuffers(1, &element_buffer_object_);

    glGenVertexArrays(1, &vertex_buffer_object_);

    glBindVertexArray(vertex_array_object_);
    {
        glBindBuffer(GL_VERTEX_ARRAY, vertex_array_object_);
        glBufferData(GL_VERTEX_ARRAY, (*vertex_data).GetDataSize(), (*vertex_data).GetRawData(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer_object_);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, (*indicies).GetDataSize(), (*indicies).GetRawData(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(0));
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
        glEnableVertexAttribArray(2);
    }
    glBindVertexArray(0);
}

void GLTestCube::BindToRender()
{
    glBindVertexArray(vertex_array_object_);
}

void GLTestCube::DeleteResources()
{
    std::cout << "GLTestCube::DeleteResources() not implemented!" << std::endl;
}

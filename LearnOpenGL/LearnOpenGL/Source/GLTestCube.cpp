#include <iostream>
#include <glm\vec3.hpp>
#include <glm\matrix.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include "..\Include\RenderingSystem\GLObject\GLTestCube.h"

GLTestCube::GLTestCube(std::shared_ptr<VertexData> vertex_data, std::shared_ptr<Material> material) :
    GLObject(vertex_data, material)
{
    LoadVertexData(vertex_data);
}

GLTestCube::~GLTestCube()
{
    delete world_position_;
    delete world_euler_;
    delete world_scale_;
}

void GLTestCube::LoadVertexData(std::shared_ptr<VertexData> vertex_data)
{
    glGenBuffers(1, &vertex_buffer_object_);
    glGenVertexArrays(1, &vertex_array_object_);

    glBindVertexArray(vertex_array_object_);
    
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object_);
	glBufferData(GL_ARRAY_BUFFER, vertex_data->GetDataSize(), vertex_data->GetRawData(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
}

void GLTestCube::BindToRender(glm::mat4& view_matrix,
                              glm::mat4& perspective_matrix)
{
    glBindVertexArray(vertex_array_object_);
    
    GetMainMaterial().PrepareToDraw();
    GetMainMaterial().SendTransformData(GetModelMatrix(), view_matrix, perspective_matrix);
}

void GLTestCube::DrawCall()
{
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

#include <iostream>
#include <glm\vec3.hpp>
#include <glm\matrix.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include "..\Include\RenderingSystem\GLObject\GLTestCube.h"

GLTestCube::GLTestCube(std::shared_ptr<VertexData> vertex_data, std::shared_ptr<ShaderProgram> shader_program) :
    GLObject(vertex_data, shader_program)
{
    //LoadVertexData(vertex_data);
}

GLTestCube::~GLTestCube()
{
    delete world_position_;
    delete world_euler_;
    delete world_scale_;
}

void GLTestCube::LoadVertexData(std::shared_ptr<VertexData> vertex_data)
{
    glGenBuffers(1, &vertex_array_object_);
    glGenBuffers(1, &element_buffer_object_);

    glGenVertexArrays(1, &vertex_buffer_object_);

    glBindVertexArray(vertex_array_object_);
    {
        glBindBuffer(GL_VERTEX_ARRAY, vertex_array_object_);
        glBufferData(GL_VERTEX_ARRAY, (*vertex_data).GetDataSize(), (*vertex_data).GetRawData(), GL_STATIC_DRAW);


        // Need remap here
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

void GLTestCube::DrawCall()
{
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void GLTestCube::DeleteResources()
{
    std::cout << "GLTestCube::DeleteResources() not implemented!" << std::endl;
}

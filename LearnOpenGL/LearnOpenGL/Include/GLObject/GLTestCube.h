#ifndef __GL_CUBE_H__
#define __GL_CUBE_H__

#include <gl\glew.h>
#include <glm\fwd.hpp>

#include "GLObject.h"

class GLTestCube : public GLObject
{
public:
    GLTestCube                                          (std::shared_ptr<VertexData> vertex_data, std::shared_ptr<ShaderProgram> shader_program);
    virtual ~GLTestCube                                 ();

    glm::mat4           GetModelMatrix                  ();
    glm::mat4           GetViewMatrix                   (const glm::vec3& camera_pos, const glm::vec3& camera_dir);
    glm::mat4           GetProjMatrix                   (const GLfloat aspect_ratio, const GLfloat fow);

    void                SetWorldPosition                (const glm::vec3& position);
    void                SetWorldRotation                (const glm::vec3& euler_angles);
    void                SetWorldScale                   (const glm::vec3& scale);

    // ============ Public interface ============
    virtual void        LoadVertexData                  (std::shared_ptr<VertexData> vertex_data, std::shared_ptr<VertexData> indicies) override;

    virtual void        BindToRender                    () override;
    virtual void        DeleteResources                 () override;

protected:

    // Transformation data
    glm::vec3* world_position_   = nullptr;
    glm::vec3* world_euler_      = nullptr;
    glm::vec3* world_scale_      = nullptr;

    GLuint vertex_array_object_     = 0;
    GLuint element_buffer_object_   = 0;
    GLuint vertex_buffer_object_    = 0;
};

#endif
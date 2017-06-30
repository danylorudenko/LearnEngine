#ifndef __GL_CUBE_H__
#define __GL_CUBE_H__

#include <gl\glew.h>
#include <glm\fwd.hpp>

#include "GLObject.h"

class GLTestCube : public GLObject
{
public:
    GLTestCube                                          (std::shared_ptr<VertexData> vertex_data, std::shared_ptr<Material> shader_program);
    virtual ~GLTestCube                                 ();

    // ============ Data Management ============
    virtual void        LoadVertexData                  (std::shared_ptr<VertexData> vertex_data) override;
    virtual void        BindToRender                    (glm::mat4& view_matrix,
                                                         glm::mat4& perspective_matrix) override;

    virtual void        DrawCall                        () override;

protected:

    GLuint vertex_array_object_     = 0;
    GLuint element_buffer_object_   = 0;
    GLuint vertex_buffer_object_    = 0;
};

#endif
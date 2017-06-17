#ifndef __GL_OBJECT__
#define __GL_OBJECT__

#include <memory>
#include <glm\fwd.hpp>

#include "..\..\Shaders\ShaderProgram.h"
#include "..\..\Util\VertexData.h"

class GLObject
{
public:
    // ========== Construction and operators ==========

    GLObject                                     (std::shared_ptr<VertexData> vertex_data, std::shared_ptr<ShaderProgram> shader_program);
    virtual ~GLObject                            ();

    GLObject                                     (const GLObject& rhs) = delete;
    GLObject&                operator=           (const GLObject& rhs) = delete;
    
    GLObject                                     (GLObject&& rhs);
    GLObject&                operator=           (GLObject&& rhs) = delete;


    // ========== GL API ==========

    virtual void        LoadVertexData           (std::shared_ptr<VertexData> vertex_data) = 0;
    virtual void        BindToRender             () = 0;
    virtual void        DrawCall                 () = 0;
    virtual void        DeleteResources          () = 0;

protected:
    std::shared_ptr<ShaderProgram>      main_shader_program_;
    std::shared_ptr<VertexData>         vertex_data_;


    // ========== Transformations ==========
public:
    virtual glm::mat4   GetModelMatrix           ();

    virtual void        SetWorldPosition         (const glm::vec3& position);
    virtual void        SetWorldRotation         (const glm::vec3& euler_angles);
    virtual void        SetWorldScale            (const glm::vec3& scale);

    glm::vec3* world_position_  = nullptr;
    glm::vec3* world_euler_     = nullptr;
    glm::vec3* world_scale_     = nullptr;
    
};

#endif
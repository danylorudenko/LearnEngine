#ifndef __GL_OBJECT__
#define __GL_OBJECT__

#include <memory>
#include <glm\fwd.hpp>

#include "..\Camera.h"
#include "..\..\Shaders\ShaderProgram.h"
#include "..\..\Texture\DoubleTextureController.h"
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
    virtual void        DrawCall                 (std::shared_ptr<Camera> camera, int viewport_width, int viewport_height) = 0;
    virtual void        DeleteResources          () = 0;

    virtual void        SetMainShader            (std::shared_ptr<ShaderProgram> shader);
    virtual void        SetMainTexture           (std::shared_ptr<DoubleTextureController> texture);

protected:
    std::shared_ptr<ShaderProgram>          main_shader_program_;
    std::shared_ptr<DoubleTextureController>    main_texture_;
    std::shared_ptr<VertexData>             vertex_data_;


    // ========== Transformations ==========
public:
    virtual glm::mat4   GetModelMatrix                     ();

    virtual void        SetWorldPosition                   (const glm::vec3& position);
    virtual void        SetWorldRotation                   (const glm::vec3& euler_angles);
    virtual void        SetWorldScale                      (const glm::vec3& scale);

protected:
    virtual void        UseShader_SendTransfromData        (std::shared_ptr<Camera> camera, int viewport_width, int viewport_height);

protected:
    glm::vec3* world_position_  = nullptr;
    glm::vec3* world_euler_     = nullptr;
    glm::vec3* world_scale_     = nullptr;
    
};

#endif
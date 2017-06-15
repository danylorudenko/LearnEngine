#ifndef __GL_OBJECT__
#define __GL_OBJECT__

#include <memory>

#include "..\Shaders\ShaderProgram.h"
#include "..\Util\VertexData.h"

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


    // ========== Public interface ==========

    virtual void             LoadVertexData      (std::shared_ptr<VertexData> vertex_data, std::shared_ptr<VertexData> indicies) = 0;
    virtual void             Render              () = 0;

    // ========== Utils ========
    virtual void             BindToRender        () = 0;
    virtual void             DeleteResources     () = 0;

protected:
    std::shared_ptr<ShaderProgram>      main_shader_program_;
    std::shared_ptr<VertexData>         vertex_data_;
};

#endif
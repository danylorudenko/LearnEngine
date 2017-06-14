#ifndef __GL_OBJECT__
#define __GL_OBJECT__

#include <memory>

#include "Shaders\ShaderProgram.h"
#include "VertexData.h"

class GLObject
{
public:
    // ========== Construction and operators ==========

    GLObject                                     ();
    ~GLObject                                    ();

    GLObject                                     (const GLObject& rhs) = delete;
    GLObject&                operator=           (const GLObject& rhs) = delete;
    
    GLObject                                     (GLObject&& rhs);
    GLObject&                operator=           (GLObject&& rhs) = delete;


    // ========== Public interface ==========

    virtual void             SetVertexData       (VertexData&& data) = 0;
    virtual void             CompileMainShader   (const GLchar* vertex_shader, const GLchar* fragment_shader) = 0;
    virtual void             Render              () = 0;

    // ========== Utils ========

    virtual void             DeleteResources     () = 0;

    // ========== Private members ==========

private:
    std::shared_ptr<ShaderProgram>      main_shader_program_;
    std::shared_ptr<VertexData>         vertex_data_;
};

#endif
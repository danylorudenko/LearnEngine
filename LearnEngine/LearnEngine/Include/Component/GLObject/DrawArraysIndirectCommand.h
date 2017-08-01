#ifndef __DRAW_ARRAYS_INDIRECT_COMMAND_H__
#define __DRAW_ARRAYS_INDIRECT_COMMAND_H__

#include <GL\glew.h>

// Wrapper for indirect array-drawing command.
// Used to tell OpenGL params for indirect dwawing (vertex count, instance count, bases).
class DrawArraysIndirectCommand
{
    // Format of default data in the DrawArray indirect command.
    // GLuint vertex_count      = 0;
    // GLuint instances_count   = 1;
    // GLuint firstVertex       = 0;
    // GLuint baseInstance      = 0;
protected:
    static constexpr GLsizei VERTEX_COUNT_OFFSET    = 0 * sizeof(GLuint);
    static constexpr GLsizei INSTANCE_COUNT_OFFSET  = 1 * sizeof(GLuint);
    static constexpr GLsizei FIRST_VERTEX_OFFSET    = 2 * sizeof(GLuint);
    static constexpr GLsizei BASE_INSTANCE_OFFSET   = 3 * sizeof(GLuint);

    static constexpr GLsizei BUFFER_SIZE            = 4 * sizeof(GLuint);

public:
    DrawArraysIndirectCommand               ();
    ~DrawArraysIndirectCommand              ();

    DrawArraysIndirectCommand               (const DrawArraysIndirectCommand& rhs);
    DrawArraysIndirectCommand&  operator=   (const DrawArraysIndirectCommand& rhs);
    DrawArraysIndirectCommand               (DrawArraysIndirectCommand&& rhs);
    DrawArraysIndirectCommand&  operator=   (DrawArraysIndirectCommand&& rhs);

    // Allocate GPU buffer of proper size for indirect command.
    void    Allocate                        ();

    // Delete allocatd GPU buffer.
    void    Deallocate                      ();

    // Bind indirect command buffer to the target (GL_DRAW_INDIRECT_BUFFER).
    void    Bind                            () const;

    // Set count of vertices to draw.
    void    SetVertexCount                  (GLuint vertex_count);

    // Set count of instances to be drawn.
    void    SetInstanceCount                (GLuint instance_count);

    // Set Offset of the first vertex in bytes in the vertex buffer to be drawn.
    void    SetFirstVertexOffset            (GLuint first_vertex_offset);

    // Set offset for the instance counter used in instanced rendering.
    void    SetBaseInstance                 (GLuint base_instance_offset);

    // Mapping GPU buffer for reading only.
    void*   MapRead                         () const;

    // Mapping GPU buffer for writing only.
    void*   MapWrite                        ();

    // Mapping GPU buffer for both reading and writing.
    void*   MapReadWrite                    ();

    // Unmapping GPU buffer.
    void    Unmap                           () const;


protected:
    GLuint  buffer_handle_;
    
    // Default data to be filled in the internal GPU buffer.
    static constexpr GLuint  DEFAULT_DATA[]         = { 0, 1, 0, 0 };
};

#endif
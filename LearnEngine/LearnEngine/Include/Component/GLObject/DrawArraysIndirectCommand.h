#ifndef __DRAW_ARRAYS_INDIRECT_COMMAND_H__
#define __DRAW_ARRAYS_INDIRECT_COMMAND_H__

#include <GL\glew.h>

class DrawArraysIndirectCommand
{
    //GLuint vertex_count;
    //GLuint instances_count;
    //GLuint firstVertex;
    //GLuint baseInstance;
public:
    static constexpr GLsizei VERTEX_COUNT_OFFSET    = 0 * sizeof(GLuint);
    static constexpr GLsizei INSTANCE_COUNT_OFFSET  = 1 * sizeof(GLuint);
    static constexpr GLsizei FIRST_VERTEX_OFFSET    = 2 * sizeof(GLuint);
    static constexpr GLsizei BASE_INSTANCE_OFFSET   = 3 * sizeof(GLuint);

    static constexpr GLsizei BUFFER_SIZE            = 4 * sizeof(GLuint);

    DrawArraysIndirectCommand               ();
    ~DrawArraysIndirectCommand              ();

    DrawArraysIndirectCommand               (const DrawArraysIndirectCommand& rhs) = delete;
    DrawArraysIndirectCommand&  operator=   (const DrawArraysIndirectCommand& rhs) = delete;
    DrawArraysIndirectCommand               (DrawArraysIndirectCommand&& rhs) = delete;
    DrawArraysIndirectCommand&  operator=   (DrawArraysIndirectCommand&& rhs) = delete;



    void    Allocate    ();
    void    Deallocate  ();
    void    Bind        () const;

    void*   MapRead     ();
    void*   MapWrite    ();
    void*   MapReadWrite();
    void    Unmap       ();


protected:
    GLuint  buffer_handle_;
    
    static constexpr GLuint  DEFAULT_DATA[]         = { 0, 1, 0, 0 };
};

#endif
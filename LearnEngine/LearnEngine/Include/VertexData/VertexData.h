#ifndef __VERTEX_DATA_H__
#define __VERTEX_DATA_H__

#include <vector>

#include <gl\glew.h>
#include "DrawArraysIndirectCommand.h"
#include "VertexAttribData.h"

// Wrapper to hold binary vertex data in the RAM and in GPU buffer + data needed to set state to render internal vertex data.
class VertexData
{
public:

    // =============== Initialization =================
    VertexData                                              (void* data, GLuint vertex_count, GLsizei size, GLsizei stride, GLuint offset);

    VertexData                                              (const VertexData& rhs) = delete;
    VertexData&                         operator=           (const VertexData& rhs) = delete;

    VertexData                                              (VertexData&& rhs) = delete;
    VertexData&                         operator=           (VertexData&& rhs) = delete;

    void                                SetDrawCommand      (const DrawArraysIndirectCommand& command);
    void                                SetDrawCommand      (DrawArraysIndirectCommand&& command);

    // ================ General ==================

    // Bind all needed data to render internal vertex data.
    void                                Bind                () const;

    // Bind indeirect draw command.
    void                                BindDrawCommand     () const;

    // Bind Vertex Array Object describing vertex data.
    void                                BindVAO             () const;

    // Size of internal data array in bytes.
    GLsizei                             RawDataSize         () const;

    // Get pointer to raw vertex data in RAM.
    void*                               RawData             () const;

    // Count of vertices in RAM that can be renderd together.
    GLuint                              VertexCount         () const;

    // Offset of the vertex data in the internal RAM memory.
    GLuint                              Offset              () const; 

    // Stride between vertices in the internal RAM memory.
    GLsizei                             Stride              () const;



    // ================ Attributes data manipulation ===================
    
    // Add VertrexAttribData describing vertex attribute.
    // Automatically attaches vertex attribute data to the VAO.
    void                    AddVAOVertexAttrib              (const VertexAttribData& data);

    virtual ~VertexData                                     ();

protected:
    // Create Vertex Array Object on GPU.
    void                    CreateVAO                       ();

    // Delete Vertex Array Object from GPU.
    void                    DeleteVAO                       ();

    // Allocate VBO on GPU to hold vertex data and fill it with vertex data from RAM.
    void                    CreateAndFillVertexBuffer       ();

    // Delete VBO from GPU.
    void                    DeleteVertexBuffer              ();

protected:
    void*                                                   vertex_data_;

    // ========= Discriptional general data ==========

    GLsizei                                                 data_size_;
    GLsizei                                                 stride_;
    GLuint                                                  vertex_count_;
    GLuint                                                  vertex_data_offset_;
    
    // ========= GL objects =============

    GLuint                                                  vertex_buffer_object_;
    GLuint                                                  vertex_array_object_;
    
    // ========= DrawInfoDescription ===========

    DrawArraysIndirectCommand                               draw_arrays_command_;
};

#endif
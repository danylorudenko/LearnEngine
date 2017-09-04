#ifndef __TEXTURE_CONTROLLER_H__
#define __TEXTURE_CONTROLLER_H__

#include <string>
#include <gl\glew.h>

// Wpapper around texture binary data and texture buffer on the GPU.
// Contains state-setting logic of sampler, seperate/solid binding of texture and sampler to texture units units.
class TextureController
{
public:
    TextureController                           ();
    TextureController                           (const std::string& file_path);

    TextureController                           (const TextureController& rhs) = delete;
    TextureController&      operator=           (const TextureController& rhs) = delete;
    TextureController                           (TextureController&& rhs) = delete;
    TextureController&      operator=           (TextureController&& rhs) = delete;

    virtual ~TextureController                  ();

public:
    GLuint                  GetTextureHandle    ();
    GLuint                  GetSamplerHandle    ();

    // Bind both sampler and texture buffer to the single texture_unit
    void                    BindAllToUnit       (GLuint texture_unit) const;

    // Bind only texture buffer to the texture unit.
    void                    BindTextureToUnit   (GLuint texture_unit) const;
    
    // Bind only sampler to the texture unit.
    void                    BindSamplerToUnit   (GLuint texture_unit) const;

    void                    SetSamplerParam     (GLenum p_name, GLint param);
    void                    SetSamplerParam     (GLenum p_name, GLfloat param);

    // Does TextureController have binary data of the texture in RAM?
    bool                    IsInRAM             () const;

    // Does TextureController have a filled texture buffer on GPU? 
    bool                    IsOnGPU             () const;

    // Load texture binary data from disk to RAM.
    virtual void            LoadToRAM           ();

    // Load texture binary data from RAM to GPU buffer.
    virtual void            LoadToGPU           ();

    // Delete texture memory in RAM.
    virtual void            UnloadFromRAM       ();

    // Delete texture buffer on GPU.
    virtual void            UnloadFromGPU       ();

protected:
    void                    SetupDefaultSamler  ();

protected:
    std::string             file_path_;

    GLuint                  texture_handle_;
    GLuint                  sampler_handle_;

    unsigned char*          image_data_;
    int                     width_;
    int                     height_;

    bool                    is_in_memory_;
    bool                    is_on_GPU_;
};

#endif
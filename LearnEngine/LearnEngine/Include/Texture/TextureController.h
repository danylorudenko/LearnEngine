#ifndef __TEXTURE_CONTROLLER_H__
#define __TEXTURE_CONTROLLER_H__

#include <string>
#include <GL\glew.h>

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

    void                    BindAllToUnit       (GLuint texture_unit) const;
    void                    BindTextureToUnit   (GLuint texture_unit) const;
    void                    BindSamplerToUnit   (GLuint texture_unit) const;

    void                    SetSamplerParam     (GLenum p_name, GLint param);
    void                    SetSamplerParam     (GLenum p_name, GLfloat param);

    bool                    IsInMemory          () const;
    bool                    IsOnGPU             () const;

    virtual void            LoadTextureData     ();
    virtual void            LoadToGL            ();

    virtual void            UnloadFromMemory    ();
    virtual void            UnloadFromGL        ();

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
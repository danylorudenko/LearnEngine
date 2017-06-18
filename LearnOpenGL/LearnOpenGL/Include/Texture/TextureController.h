#ifndef __TEXTURE_CONTROLLER_H__
#define __TEXTURE_CONTROLLER_H__

#include <string>
#include <GL\glew.h>

class TextureController
{
public:
    TextureController                       ();
    TextureController                       (const std::string& file_path);

    TextureController                       (const TextureController& rhs) = delete;
    TextureController&      operator=       (const TextureController& rhs) = delete;
    TextureController                       (TextureController&& rhs) = delete;
    TextureController&      operator=       (TextureController&& rhs) = delete;

    virtual ~TextureController              ();

public:
    void                    LoadTextureData ();
    void                    LoadToGL        ();

    void                    UnloadFromMemory();
    void                    UnloadFromGL    ();

    void                    Bind            ();

protected:
    std::string             file_path_;
    GLuint                  texture_handle_;

    unsigned char*          image_data_;
    int                     width_;
    int                     height_;
};

#endif
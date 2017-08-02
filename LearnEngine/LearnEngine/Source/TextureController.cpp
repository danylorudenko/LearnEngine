#include "..\Include\Texture\TextureController.h"
#include "..\Include\Util\Debugging\DebugTools.h"

#include <SOIL\SOIL.h>
#include <stdexcept>

TextureController::TextureController() : 
    texture_handle_(0),
    sampler_handle_(0),
    image_data_(nullptr),
    width_(0),
    height_(0),
    is_in_memory_(false),
    is_on_GPU_(false)
{
    SetupDefaultSamler();
}

TextureController::TextureController(const std::string& file_path) : file_path_(file_path)
{
    SetupDefaultSamler();
    LoadToMemory();
    LoadToGL();
}

void TextureController::LoadToMemory()
{
    image_data_ = SOIL_load_image(file_path_.c_str(), &width_, &height_, nullptr, SOIL_LOAD_RGB);

    if (image_data_ == nullptr) {
        throw std::runtime_error(std::string("Error loading texture at path: ") + file_path_);
    }

    is_in_memory_ = true;
}

void TextureController::UnloadFromMemory()
{
    SOIL_free_image_data(image_data_);
    image_data_ = nullptr;
    is_in_memory_ = false;
}

void TextureController::LoadToGL()
{
    if (image_data_ == nullptr) {
        throw std::runtime_error("Can't load texture to the GL. No data in RAM.");
    }
    
    display_gl_errors();

    glCreateTextures(GL_TEXTURE_2D, 1, &texture_handle_);

    display_gl_errors();

    // Allocating storage.
    glTextureStorage2D(
        texture_handle_,
        1, // Mipmaps
        GL_RGB8,
        width_,
        height_
    );

    display_gl_errors();

    glTextureSubImage2D(
        texture_handle_,
        0, // Mipmaps
        0, 0,
        width_, height_,
        GL_RGB,
        GL_UNSIGNED_BYTE,
        image_data_
    );

    is_on_GPU_ = true;

	display_gl_errors();
}

void TextureController::UnloadFromGL()
{
    glDeleteTextures(1, &texture_handle_);
    texture_handle_ = 0;
    is_on_GPU_ = false;
}

TextureController::~TextureController()
{
    UnloadFromGL();
    UnloadFromMemory();
    glDeleteSamplers(1, &sampler_handle_);
}

GLuint TextureController::GetTextureHandle()
{
    return texture_handle_;
}

GLuint TextureController::GetSamplerHandle()
{
    return sampler_handle_;
}

void TextureController::BindAllToUnit(GLuint texture_unit) const
{
    BindSamplerToUnit(texture_unit);
    BindTextureToUnit(texture_unit);
}

void TextureController::BindSamplerToUnit(GLuint texture_unit) const
{
    glBindSampler(texture_unit, sampler_handle_);
}

void TextureController::BindTextureToUnit(GLuint texture_unit) const
{
    glBindTextureUnit(texture_unit, texture_handle_);
}

void TextureController::SetupDefaultSamler()
{
    glCreateSamplers(1, &sampler_handle_);
    SetSamplerParam(GL_TEXTURE_WRAP_S, GL_REPEAT);
    SetSamplerParam(GL_TEXTURE_WRAP_T, GL_REPEAT);

    SetSamplerParam(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    SetSamplerParam(GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    display_gl_errors();
}

void TextureController::SetSamplerParam(GLenum p_name, GLint param)
{
    glSamplerParameteri(sampler_handle_, p_name, param);
}

void TextureController::SetSamplerParam(GLenum p_name, GLfloat param)
{
    glSamplerParameterf(sampler_handle_, p_name, param);
}

bool TextureController::IsInMemory() const
{
    return is_in_memory_;
}

bool TextureController::IsOnGPU() const
{
    return is_on_GPU_;
}

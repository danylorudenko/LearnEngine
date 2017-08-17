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

TextureController::TextureController(const std::string& file_path) : 
    file_path_(file_path),
    texture_handle_(0),
    sampler_handle_(0),
    image_data_(nullptr),
    width_(0),
    height_(0),
    internal_format_(0),
    is_in_memory_(false),
    is_on_GPU_(false)
{
    SetupDefaultSamler();
    LoadToRAM(file_path_);
    AllocateOnGPU(width_, height_, internal_format_);
    LoadToGPU();
}

void TextureController::LoadToRAM(const std::string& source_file)
{
    file_path_ = source_file;
    image_data_ = SOIL_load_image(source_file.c_str(), &width_, &height_, nullptr, SOIL_LOAD_RGB);

    if (image_data_ == nullptr) {
        throw std::runtime_error(std::string("Error loading texture at path: ") + file_path_);
    }

    internal_format_ = GL_RGB;
    is_in_memory_ = true;
}

void TextureController::AllocateOnGPU(GLsizei width, GLsizei height, GLenum internal_format, GLsizei mipmaps)
{
    if (texture_handle_ != 0) {
        throw std::runtime_error(std::string("Texture is already on GPU. Can't allocate new storage."));
    }
    
#ifdef GL44

    glGenTextures(GL_TEXTURE_2D, 1, &texture_handle_);
    glBindTexture(GL_TEXTURE_2D, texture_handle_);

    glTexStorage2D(
        GL_TEXTURE_2D,
        mipmaps,
        internal_format,
        width,
        height
    );

#else

    glCreateTextures(GL_TEXTURE_2D, 1, &texture_handle_);

    glTextureStorage2D(
        texture_handle_,
        mipmaps,
        internal_format,
        width,
        height
    );

#endif
}

void TextureController::UnloadFromRAM()
{
    SOIL_free_image_data(image_data_);
    image_data_ = nullptr;
    is_in_memory_ = false;

    if (!IsOnGPU()) {
        width_ = 0;
        height_ = 0;
        internal_format_ = 0;
    }
}

void TextureController::LoadToGPU()
{
    if (image_data_ == nullptr) {
        throw std::runtime_error("Can't load texture to the GL. No data in RAM.");
    }

    if (texture_handle_ == 0) {
        throw std::runtime_error("Can't load texture to GL. No texture was allocated.");
    }
    
#ifdef GL44

    glBindTexture(GL_TEXTURE_2D, texture_handle_);
    glTexSubImage2D(
        GL_TEXTURE_2D,
        0, // Mipmaps
        0, 0,
        width_, height_,
        GL_RGB,
        GL_UNSIGNED_BYTE,
        image_data_
    );

#else

    glTextureSubImage2D(
        texture_handle_,
        0, // Mipmaps
        0, 0,
        width_, height_,
        GL_RGB,
        GL_UNSIGNED_BYTE,
        image_data_
    );

#endif

    is_on_GPU_ = true;

	display_gl_errors();
}

void TextureController::UnloadFromGPU()
{
    glDeleteTextures(1, &texture_handle_);
    texture_handle_ = 0;
    is_on_GPU_ = false;
}

TextureController::~TextureController()
{
    UnloadFromGPU();
    UnloadFromRAM();
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

const std::string & TextureController::FileName() const
{
    return file_path_;
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
#ifdef GL44

    glActiveTexture(GL_TEXTURE0 + texture_unit);
    glBindTexture(GL_TEXTURE_2D, texture_handle_);

    display_gl_errors();

#else

    glBindTextureUnit(texture_unit, texture_handle_);

#endif
}

void TextureController::SetupDefaultSamler()
{
    glGenSamplers(1, &sampler_handle_);
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

bool TextureController::IsInRAM() const
{
    return is_in_memory_;
}

bool TextureController::IsOnGPU() const
{
    return is_on_GPU_;
}
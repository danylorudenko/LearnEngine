#include "..\Include\Texture\TextureController.h"

#include <SOIL\SOIL.h>
#include <stdexcept>

TextureController::TextureController() : 
    texture_handle_(0), 
    image_data_(nullptr),
    width_(0),
    height_(0)
{

}

TextureController::TextureController(const std::string& file_path) : file_path_(file_path)
{
    LoadTextureData();
    LoadToGL();
}

void TextureController::LoadTextureData()
{
    image_data_ = SOIL_load_image(file_path_.c_str(), &width_, &height_, nullptr, SOIL_LOAD_RGB);

    if (image_data_ == nullptr) {
        throw std::runtime_error(std::string("Error loading texture at path: ") + file_path_);
    }
}

void TextureController::UnloadFromMemory()
{
    SOIL_free_image_data(image_data_);
    image_data_ = nullptr;
}

void TextureController::LoadToGL()
{
    if (image_data_ == nullptr) {
        throw std::runtime_error("Can't load texture to the GL. No data in RAM.");
    }
    
    glGenTextures(1, &texture_handle_);
    
    glBindTexture(GL_TEXTURE_2D, texture_handle_);
    
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width_, height_, 0, GL_RGB, GL_BYTE, image_data_);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void TextureController::UnloadFromGL()
{
    glDeleteTextures(1, &texture_handle_);
    texture_handle_ = 0;
}

void TextureController::Bind()
{
    glBindTexture(GL_TEXTURE_2D, texture_handle_);
}

TextureController::~TextureController()
{
    UnloadFromGL();
    UnloadFromMemory();
}
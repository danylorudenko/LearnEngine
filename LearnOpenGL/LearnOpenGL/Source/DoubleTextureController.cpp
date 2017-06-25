#include <SOIL\SOIL.h>
#include "..\Include\Texture\DoubleTextureController.h"
#include "..\Include\Util\Debugging\DebugTools.h"

DoubleTextureController::DoubleTextureController() :
    TextureController(),
    texture2_handle_(0),
    image2_data_(nullptr),
    width2_(0),
    height2_(0)
{

}

DoubleTextureController::DoubleTextureController(const std::string& file1_path, const std::string& file2_path) :
    TextureController(file1_path), file2_path_(file2_path)
{
	LoadTextureData();
    LoadToGL();
}

void DoubleTextureController::Bind()
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_handle_);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2_handle_);
}

void DoubleTextureController::LoadTextureData()
{
    TextureController::LoadTextureData();

    image2_data_ = SOIL_load_image(file2_path_.c_str(), &width2_, &height2_, nullptr, SOIL_LOAD_RGB);

    if (image2_data_ == nullptr) {
        throw std::runtime_error(std::string("Error loading texture at path: ") + file2_path_);
    }
}

void DoubleTextureController::LoadToGL()
{
    TextureController::LoadToGL();

    if (image2_data_ == nullptr) {
        throw std::logic_error("Can't load texture to the GL. No data in RAM.");
    }

    glGenTextures(1, &texture2_handle_);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2_handle_);
	display_gl_errors();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	display_gl_errors();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	display_gl_errors();

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width2_, height2_, 0, GL_RGB, GL_BYTE, image2_data_);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
	display_gl_errors();
}

void DoubleTextureController::UnloadFromGL()
{
    TextureController::UnloadFromGL();

    glDeleteTextures(1, &texture2_handle_);
    texture2_handle_ = 0;
}

void DoubleTextureController::UnloadFromMemory()
{
    TextureController::UnloadFromMemory();
    
    SOIL_free_image_data(image2_data_);
    image2_data_ = nullptr;
}
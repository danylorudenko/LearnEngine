#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include <memory>

#include "..\Shaders\ShaderProgram.h"
#include "..\Texture\DoubleTextureController.h"

class Material
{
protected:
    std::shared_ptr<ShaderProgram> shader_;
    std::shared_ptr<DoubleTextureController>
};

#endif
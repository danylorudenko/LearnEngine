#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include <memory>
#include <tuple>
#include <vector>
#include "..\RenderingSystem\Camera.h"
#include "..\Shaders\ShaderProgram.h"
#include "..\Texture\TextureController.h"

class Material
{
protected:
    using UnitTexturePair = std::tuple<GLuint, std::shared_ptr<TextureController>>;
    using UnitTexturePairList = std::vector<UnitTexturePair>;

public:
    Material                                                    (std::shared_ptr<ShaderProgram> shader);
    Material                                                    (const Material& rhs);
    Material&                           operator=               (const Material& rhs);

    Material                                                    (Material&& rhs) = delete;
    Material&                           operator=               (Material&& rhs) = delete;

    virtual ~Material                                           ();


public:
    void                                SetShader               (std::shared_ptr<ShaderProgram> shader);
    void                                AddTexture              (GLuint unit, std::shared_ptr<TextureController>& texture);

    ShaderProgram&                      GetShader               ();
    std::shared_ptr<ShaderProgram>      GetShaderShared         ();

protected:
    void                                BindAllTextures         ();

protected:
    std::shared_ptr<ShaderProgram>      main_shader_;
    UnitTexturePairList                 textures_;
};

#endif
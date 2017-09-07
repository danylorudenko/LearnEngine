#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include <memory>
#include <tuple>
#include <vector>

#include <Engine\Shaders\ShaderProgram.h>
#include <Engine\Texture\TextureController.h>

namespace Engine
{

// Aggregator for the properties that can describe a physical material.
// Dependant on the main shader which material uses to provide a state for rendering.
// Contains additional unifrom properties like textures paired with texture binding unit ID.
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
    // Set main shader of the material.
    // Shaders can be shared across multiple Materials.
    void                                SetShader               (const std::shared_ptr<ShaderProgram>& shader);

    // Add new texture paired with texture unit to be binded to.
    // If there is a texture already paired with that unit, new texture replases the old one.
    void                                AddTexture              (GLuint unit, const std::shared_ptr<TextureController>& texture);

    // Remove Unit-Texture pair with the passed unit.
    void                                RemoveTexture           (GLuint unit);

    ShaderProgram&                      GetShader               ();
    std::shared_ptr<ShaderProgram>      GetShaderShared         ();

    // Bind all textures to paired texture units.
    void                                BindAllTextures         ();

protected:
    std::shared_ptr<ShaderProgram>      main_shader_;
    UnitTexturePairList                 textures_;
};

} // namespace Engine

#endif
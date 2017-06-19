#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include <memory>
#include "..\RenderingSystem\Camera.h"
#include "..\Shaders\ShaderProgram.h"
#include "..\Texture\TextureController.h"

class Material
{
public:
    Material                                    (std::shared_ptr<ShaderProgram> shader);
    Material                                    (const Material& rhs);

    Material                                    (Material&& rhs) = delete;
    Material            operator=               (Material&& rhs) = delete;

    virtual ~Material                           ();


public:
    void                                SetMainShader           (std::shared_ptr<ShaderProgram> shader);
    void                                SetMainTexture          (std::shared_ptr<TextureController> texture);

    std::shared_ptr<ShaderProgram>      GetMainShader           ();
    virtual void                        UseMainShader();
    void                                SendTransformData       (std::shared_ptr<Camera> camera, glm::mat4& model_matrix, int viewport_width, int viewport_height);

protected:
    std::shared_ptr<ShaderProgram>              main_shader_;
    std::shared_ptr<TextureController>          main_texture_;
};

#endif
#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include <memory>
#include "..\RenderingSystem\Camera.h"
#include "..\Shaders\ShaderProgram.h"
#include "..\Texture\TextureController.h"

class Material
{
public:
    Material                                                    (std::shared_ptr<ShaderProgram> shader);
    Material                                                    (const Material& rhs);

    Material                                                    (Material&& rhs) = delete;
    Material                            operator=               (Material&& rhs) = delete;

    virtual ~Material                                           ();


public:
    void                                SetMainShader           (std::shared_ptr<ShaderProgram> shader);
    void                                SetMainTexture          (std::shared_ptr<TextureController> texture);

    ShaderProgram&                      GetMainShader           ();
    TextureController&                  GetMainTexture          ();

    void                                SendTransformData       (glm::mat4& model_matrix, 
                                                                 glm::mat4& view_matrix, 
                                                                 glm::mat4& perspective_matrix);
    virtual void                        PrepareToDraw           ();

protected:
    std::shared_ptr<ShaderProgram>      main_shader_;
    std::shared_ptr<TextureController>  main_texture_;
};

#endif
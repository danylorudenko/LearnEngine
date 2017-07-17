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
    Material                            operator=               (const Material& rhs);

    Material                                                    (Material&& rhs) = delete;
    Material&                           operator=               (Material&& rhs) = delete;

    virtual ~Material                                           ();


public:
    void                                SetMainShader           (std::shared_ptr<ShaderProgram> shader);

    ShaderProgram&                      GetMainShader           ();
    TextureController&                  GetMainTexture          ();

    virtual void                        Bind                    ();

protected:
    virtual void                        BindTransformBlock      ();

protected:
    std::shared_ptr<ShaderProgram>      main_shader_;
    std::shared_ptr<TextureController>  main_texture_;
};

#endif
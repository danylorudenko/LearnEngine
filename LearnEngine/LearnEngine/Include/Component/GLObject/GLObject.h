#ifndef __GL_OBJECT__
#define __GL_OBJECT__

#include <memory>
#include <glm\vec3.hpp>

#include "..\Component.h"
#include "DrawArraysIndirectCommand.h"
#include ".\GLTransformation\GLTransform.h"
#include "..\..\Material\Material.h"
#include "..\..\VertexData\VertexData.h"

// Represents component that allows entity to be drawn in the scene.
// Supports GPU uniform transformation buffer.
// Can override transformation logic of the owner entity.
class GLObject : public Component, public GLTransform
{
protected:
    // ========== Component interface =============
    virtual void            RegisterInSystem        () override;
    virtual void            UnregisterFromSystem    () override;


public:
    // ========== Construction and operators ==========

    GLObject                                        (std::shared_ptr<VertexData> vertex_data, std::shared_ptr<Material> main_material);
    GLObject                                        (const GLObject& rhs) = delete;
                                                    
    GLObject&                operator=              (const GLObject& rhs) = delete;
    GLObject                                        (GLObject&& rhs) = delete;
    GLObject&                operator=              (GLObject&& rhs) = delete;

    virtual ~GLObject();


    // ========== GL API ==========
public:

    virtual void                        SetVertexData               (std::shared_ptr<VertexData>& vertex_data);
    virtual void                        BindToRender                ();

    virtual std::shared_ptr<Material>   GetMainMaterialShared       ();
    virtual Material&                   GetMainMaterial             ();

protected:
    // Binding data for the standartized shader uniform block.
    // Conventional standard uniform block contains:
    //      - common data from rendering system (camera position);
    //      - transformation data;
    //      - sampler2D (main texture);
    virtual void                        BindStandardUnifromBlocks   ();

protected:
    std::shared_ptr<Material>           main_material_;
    std::shared_ptr<VertexData>         vertex_data_;

};

#endif
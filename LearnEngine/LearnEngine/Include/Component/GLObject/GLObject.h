#ifndef __GL_OBJECT__
#define __GL_OBJECT__

#include <memory>

#include "..\Component.h"
#include "DrawArraysIndirectCommand.h"
#include "..\..\Material\Material.h"
#include "..\..\VertexData\VertexData.h"

// Represents component that allows Entity to be drawn in the scene.
// Contains logic for setting context of OpenGL.
class GLObject : public Component
{
protected:
    // ========== Component interface =============
    
    // Perform proper registration of the GLObject in Rendering system.
    // Registration is performed right after component is added to Entity.
    virtual void            RegisterInSystem        () override;

    // Perform proper removal of component by the Rendering system.
    // Removal is performed when the component is removed from the Entity
    // or when the Entity is destroyed with all it's components.
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

    // Set vertex data to be used for rendering.
    // Vertex data can be shared and used by many GLObjects.
    virtual void                        SetVertexData               (const std::shared_ptr<VertexData>& vertex_data);

    // Perform binding of all conventional and additional buffers needed for rendering of GLObject.
    virtual void                        BindToRender                ();

    virtual std::shared_ptr<Material>   GetMainMaterialShared       ();
    virtual Material&                   GetMainMaterial             ();

protected:
    // Binding data for the standartized shader uniform block.
    // GLOjbect is responisble only for binding transfrom block of the owner (for now).
    virtual void                        BindStandardUnifromBlocks   ();

protected:
    std::shared_ptr<Material>           main_material_;
    std::shared_ptr<VertexData>         vertex_data_;

};

#endif
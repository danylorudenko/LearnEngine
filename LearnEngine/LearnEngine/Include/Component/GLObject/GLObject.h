#ifndef __GL_OBJECT__
#define __GL_OBJECT__

#include <memory>
#include <glm\vec3.hpp>

#include "..\Component.h"
#include ".\GLTransformation\IGLTransformable.h"
#include "..\..\Material\Material.h"
#include "..\..\Util\VertexData.h"

// Represents component that allows entity to be drawn in the scene.
// Supports GPU uniform transformation buffer.
// Can override transformation logic of the owner entity.
class GLObject : public Component, public IGLTransformable
{
public:
    // ========== Component interface =============
    virtual void            RegisterInSystem        () override;
    virtual void            UnregisterFromSystem    () override;


public:
    // ========== Construction and operators ==========

    GLObject                                        (std::shared_ptr<VertexData> vertex_data, std::shared_ptr<Material> main_material);
    GLObject                                        (const GLObject& rhs);
                                                    
    GLObject&                operator=              (const GLObject& rhs);
    GLObject                                        (GLObject&& rhs);
    GLObject&                operator=              (GLObject&& rhs);

    virtual ~GLObject();


    // ========== GL API ==========

    static constexpr unsigned int       TRANSFORM_BUFFER_SIZE       = 3 * sizeof(glm::vec3);

    static constexpr unsigned int       POSITION_OFFSET             = 0 * sizeof(glm::vec3);
    static constexpr unsigned int       ROTATION_OFFSET             = 1 * sizeof(glm::vec3);
    static constexpr unsigned int       SCALE_OFFSET                = 2 * sizeof(glm::vec3);

    virtual void                        LoadVertexData              (std::shared_ptr<VertexData> vertex_data) = 0;
    virtual void                        BindToRender                (glm::mat4& view_matrix,
                                                                     glm::mat4& perspective_matrix) = 0;

    virtual std::shared_ptr<Material>   GetMainMaterialShared       ();
    virtual Material&                   GetMainMaterial             ();

protected:
    std::shared_ptr<Material>           main_material_;
    std::shared_ptr<VertexData>         vertex_data_;

};

#endif
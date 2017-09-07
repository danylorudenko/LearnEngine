#ifndef __CAMERA_ENTITY_H__
#define __CAMERA_ENTITY_H__

#include <GL\glew.h>
#include <glm\fwd.hpp>
#include <memory>

#include <Engine\Entity\Entity.h>

namespace Engine
{

// Aggregator for camera entity properties:
//  - transform;
//  - FOW;
//  - clipping planes.
class CameraEntity : public Entity
{
public:
    static constexpr GLfloat DEFAULT_FOW    = 60.0f;

    CameraEntity                                      (Entity* parent);
                                                
    CameraEntity                                      (const CameraEntity& rhs) = delete;
    CameraEntity              operator=               (const CameraEntity& rhs) = delete;
                                                
    CameraEntity                                      (CameraEntity&& rhs) = delete;
    CameraEntity              operator=               (CameraEntity&& rhs) = delete;

    virtual ~CameraEntity                             ();

// ========== Public interface ============

    // Create camera entity attached to the root of the World.
    static CameraEntity*      CreateCamera            ();

    // Field of view of the current camera.
    GLfloat                   GetFOW                  () const;
    GLfloat&                  GetFOW                  ();

    // Const array of two floats containing clipping planes of the camera.
    const GLfloat*            GetClippingPlanes       () const;


protected:
    GLfloat     fow_;
    GLfloat     clipping_planes_[2];

    std::unique_ptr<GLTransform> transform_;
};

} // namespace Engine

#endif
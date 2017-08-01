#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <GL\glew.h>
#include <glm\fwd.hpp>
#include <memory>

#include "..\Util\GLTransformation\GLTransform.h"

class Camera
{
public:
    static constexpr GLfloat DEFAULT_FOW    = 60.0f;

    Camera                                      (const GLfloat fow = 60);
                                                
    Camera                                      (const Camera& rhs) = delete;
    Camera              operator=               (const Camera& rhs) = delete;
                                                
    Camera                                      (Camera&& rhs) = delete;
    Camera              operator=               (Camera&& rhs) = delete;

    virtual ~Camera                             ();

// ========== Public interface ============

    GLfloat             GetFOW                  () const;
    GLTransform&        Transform               ();

    const GLfloat*      GetClippingPlanes       () const;


protected:
    GLfloat     fow_;

    GLfloat     clipping_planes_[2];

    std::unique_ptr<GLTransform> transform_;
};

#endif
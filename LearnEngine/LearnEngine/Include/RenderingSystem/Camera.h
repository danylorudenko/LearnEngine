#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <GL\glew.h>
#include <glm\fwd.hpp>

class Camera
{
public:
    static constexpr GLfloat DEFAULT_FOW    = 60.0f;

    Camera                                  (const GLfloat fow = 60);
                                            
    Camera                                  (const Camera& rhs) = delete;
    Camera          operator=               (const Camera& rhs) = delete;
                                            
    Camera                                  (Camera&& rhs) = delete;
    Camera          operator=               (Camera&& rhs) = delete;

    virtual ~Camera                         ();

// ========== Public interface ============

	void			SetWorldPosition		(glm::vec3& pos);
	void			SetViewDirection		(glm::vec3& dir);

    glm::vec3       GetWorldPosition        () const;
    glm::vec3       GetViewDirection        () const;

    GLfloat         GetFOW                  () const;

    GLfloat*        GetClippingPlanes       () const;


protected:
    GLfloat     fow_;

    GLfloat     clipping_planes_[2];

    glm::vec3*  world_position_;
    glm::vec3*  view_direction_;
};

#endif
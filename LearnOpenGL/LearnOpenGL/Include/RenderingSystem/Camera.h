#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <GL\glew.h>
#include <glm\fwd.hpp>

class Camera
{
public:
    Camera                                  (const GLfloat fow = 60);
                                            
    Camera                                  (const Camera& rhs) = delete;
    Camera          operator=               (const Camera& rhs) = delete;
                                            
    Camera                                  (Camera&& rhs) = delete;
    Camera          operator=               (Camera&& rhs) = delete;

    virtual ~Camera                         ();

// ========== Public interface ============

    glm::mat4       GetViewMatrix           () const;
    glm::mat4       GetPerspectiveMatrix    (int viewport_width, int viewport_height) const;

protected:
    GLfloat fow_;

    glm::vec3* world_position_;
    glm::vec3* view_direction_;
};

#endif
#ifndef __RENDERING_SYSTEM_H__
#define __RENDERING_SYSTEM_H__

#include "Camera.h"
#include "..\Component\GLObject\GLObject.h"
#include "..\Util\Singletone.h"

#include <GLFW\glfw3.h>

#include <list>

class RenderingSystem : public Singletone<RenderingSystem>
{
public:
    static constexpr GLfloat                        DEFAULT_FOW = 60.0f;

public:
    RenderingSystem                                 (int viewport_X, int viewport_Y,
                                                     std::shared_ptr<Camera> main_cam);

    void                Iterate                     (GLFWwindow* window);
    void                DrawAll                     (GLFWwindow* window);
    void                Clear                       ();

    void                SetMainCamera               (std::shared_ptr<Camera> main_cam);
    void                SetViewport                 (int resolution_X, int resolution_Y);
    void                AddToDrawList               (std::shared_ptr<GLObject> new_object);
    void                RemoveFromDrawList          (std::shared_ptr<GLObject> to_remove);

    static void         frame_buffer_size_callback  (GLFWwindow* window, int width, int height);

protected:
    int                                     screen_width_;
    int                                     screen_height_;

    std::shared_ptr<Camera>                 main_camera_;
    std::list<std::shared_ptr<GLObject>>    gl_objects_;
};

#endif
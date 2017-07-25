#ifndef __RENDERING_SYSTEM_H__
#define __RENDERING_SYSTEM_H__

#include "Camera.h"
#include "..\Component\GLObject\GLObject.h"
#include "RenderingSystemUniformBuffer.h"
#include "..\Util\Singletone.h"

#include <GLFW\glfw3.h>

#include <vector>

class RenderingSystem : public Singletone<RenderingSystem>
{
    using RenderingListContainter                   = std::vector<GLObject*>;

public:
    static constexpr GLfloat                        DEFAULT_FOW = 60.0f;

public:
    RenderingSystem                                 (GLFWwindow* window,
                                                     int viewport_X, int viewport_Y,
                                                     std::shared_ptr<Camera> main_cam);

    RenderingSystem                                 (const RenderingSystem& rhs) = delete;
    RenderingSystem                                 (RenderingSystem&& rhs) = delete;
    
    RenderingSystem&    operator=                   (const RenderingSystem& rhs) = delete;
    RenderingSystem&    operator=                   (RenderingSystem&& rhs) = delete;

    void                Iterate                     (GLFWwindow* window);
    void                DrawAll                     (GLFWwindow* window);
    void                Clear                       ();

    void                SetMainCamera               (std::shared_ptr<Camera> main_cam);
    void                SetViewport                 (int resolution_X, int resolution_Y);
    void                AddToDrawList               (GLObject* to_add);
    void                RemoveFromDrawList          (GLObject* to_remove);

    static void         frame_buffer_size_callback  (GLFWwindow* window, int width, int height);


protected:
    int                                     screen_width_;
    int                                     screen_height_;

    std::shared_ptr<Camera>                 main_camera_;
    RenderingListContainter                 rendering_list_;

    RenderingSystemUniformBuffer            uniform_buffer_;
};

#endif